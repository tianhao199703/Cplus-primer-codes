 void *my_memcpy(void *dst, const void *src, int n){
     if (dst == NULL || src == NULL || n <= 0)
         return NULL;
 
     int * pdst = (int *)dst;
     int * psrc = (int *)src;
     char *tmp1 = NULL;
     char *tmp2 = NULL;
     int c1 = n / 4;
     int c2 = n % 4;

     if (pdst > psrc && pdst < (char *)psrc + n){
         tmp1 = (char *)pdst + n - 1;
         tmp2 = (char *)psrc + n - 1;
         while(c2--)
             *tmp1-- = *tmp2--;
 
         tmp1++;tmp2++;
         pdst = (int *)tmp1;
         psrc = (int *)tmp2;
         pdst--;psrc--;
         while (c1--)
             *pdst-- = *psrc--;
     }
     else
     {
         while (c1--)
             *pdst++ = *psrc++;

         tmp1 = (char *)pdst;
         tmp2 = (char *)psrc;
         while (c2--)
             *tmp1++ = *tmp2++;
     }
     return dst;
 }
