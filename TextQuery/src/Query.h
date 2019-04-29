#ifndef QUERY_H_
#define QUERY_H_

#include <vector>
#include <string>
#include <memory>
#include <map>
#include <set>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
//API
class QueryResult{
	friend ostream& print(ostream&, const QueryResult&);
public:
	using line_no = vector<string>::size_type;
	QueryResult(string s, shared_ptr<set<line_no>> p, shared_ptr<vector<string>> f) :sought(s), lines(p), file(f){}
	shared_ptr<vector<string>> get_file(){ return file; }
	set<line_no>::iterator begin()const{ return lines->begin(); }//iterator
	set<line_no>::iterator end() const {return lines->end(); }
private:
	string sought;//queryed word
	shared_ptr<set<line_no>> lines;//apperent line_no
	shared_ptr<vector<string>> file;//input file
};

class TextQuery{
public:
	using line_no = vector<string>::size_type;
	TextQuery(ifstream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> file;//input file
	map<string, shared_ptr<set<line_no>>> wm;//each word to line_no
};

//REAL PROGRAM
class Query_base{//one abstract class
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;
};
class Query{//API class
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const string&);
	QueryResult eval(const TextQuery &t) const{ return q->eval(t); }
	string rep() const { return q->rep(); }
private:
	Query(shared_ptr<Query_base> query) : q(query){}
	shared_ptr<Query_base> q;
};

class WordQuery :public Query_base{
	friend class Query;
	WordQuery(const string &s) :query_word(s){}
	QueryResult eval(const TextQuery &t) const{ return t.query(query_word); }
	string rep() const { return query_word; }
	string query_word;
};
class NotQuery :public Query_base{
	friend Query operator~(const Query &);
	NotQuery(const Query &q) :query(q){}
	string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;
	Query query;
};

class BinaryQuery :public Query_base{//another abstract class
protected:
	BinaryQuery(const Query &l,const Query &r,string s):lhs(l),rhs(r),opSym(s){}
	string rep() const { return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	string opSym;
};
class AndQuery :public BinaryQuery{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "&"){}
	QueryResult eval(const TextQuery&) const;
};
class OrQuery :public BinaryQuery{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) :BinaryQuery(left, right, "|"){}
	QueryResult eval(const TextQuery&) const;
};

inline Query::Query(const string &s) :q(new WordQuery(s)){}
inline Query operator~(const Query &operand){
	return shared_ptr<Query_base>(new NotQuery(operand));
}
inline Query operator&(const Query &lhs, const Query &rhs){
	return shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}
inline Query operator|(const Query &lhs, const Query &rhs){
	return shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}
#endif