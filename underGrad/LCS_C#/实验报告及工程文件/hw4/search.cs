using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace hw4
{
    class search
    {
     public int[] s;
     public int len;
     public int mysearch(int[] temp, int reslen, int x)
            {
                int left, right, mid;
                left = 0;
                right = reslen - 1;
                
                while(left <= right)
                {
                    mid = left + (right - left) / 2;
                    if (x > temp[mid])
                        left = mid + 1;
                    else if (x < temp[mid])
                        right = mid - 1;
                    else return mid;
                }
                return left;
                
            }
     public int[] largesub(int []s, int len)
        {
            int[] temp = new int[len];
            int[] lrgsub = new int[len];
            int reslen = 1;
            temp[0] = s[0];
            lrgsub[0] = s[0];
            for (int i = 1; i < s.Length; i++)
            {
                if (s[i] >= temp[reslen - 1])
                {
                    temp[reslen] = s[i];
                    lrgsub[reslen] = s[i];
                    reslen++;
                }
                else
                {
                    int j = mysearch(temp, reslen, s[i]);
                    temp[j] = s[i];
                    if (j == reslen - 1)
                    {
                        int k = reslen - 1;
                        while (k >= 0 && lrgsub[k] != temp[i])
                        {
                            lrgsub[k] = temp[k];
                            k--;
                        }
                    }
                }
            }
               
          
            return lrgsub;
        }
    }
}
