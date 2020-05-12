vector<vector<int>> BSTSequences(TreeNode* root) {
        if (root == nullptr) return {{}};
        deque<TreeNode*> q;
        q.push_back(root);
        vector<int> buf;
        vector<vector<int>> res;
        Inner(q, buf, res);
        return res;
    }
    void Inner(deque<TreeNode*> &q,vector<int> &buf,vector<vector<int>> &res){
        if (q.empty()) {
            res.push_back(buf);
            return;
        }
        int size = q.size();
        while (size--) {
            TreeNode *r = q.front();
            q.pop_front();
            buf.push_back(r->val);
            int children = 0;
            if (r->left) {
                ++children;
                q.push_back(r->left);
            }
            if (r->right) {
                ++children;
                q.push_back(r->right);
            }
            Inner(q, buf, res);
            while (children--) {
                q.pop_back();
            }
            q.push_back(r);
            buf.pop_back();
        }
    }
