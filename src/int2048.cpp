#include "int2048.h"

namespace sjtu {

    int2048::int2048()//构造函数不需要返回值
    {
        number.clear();
        number.push_back(0);
        sign = true;
    }
    int2048::int2048(long long a)
    {
        number.clear();
        if (a == 0)
        {
            number.push_back(0);
            sign = true;
        }
        if (a < 0)
        {
            a = -a;
            sign = false;
        }
        while (a != 0)
        {
            number.push_back(a % base);
            a = a / base;
        }
    }
    int2048::int2048(const std::string& a)
    {
        number.clear();
        int len = a.size();
        int x = base, digit = 0;//digit记录基的位数
        while (x != 1)
        {
            digit++;
            x /= 10;
        }
        if (a[0] == '-')
        {
            sign = false;
            int t = 1, num = 0, basis = 1;
            for (int i = len - 1; i > 0; i--)
            {
                num += (a[i] - '0') * basis;
                basis *= 10;
                if (t == digit)
                {
                    t = 0;
                    number.push_back(num);
                    num = 0;
                    basis = 1;
                }
                if (i == 1 && t != digit)
                {
                    number.push_back(num);
                }
                t++;
            }
        }
        else
        {
            int t = 1, num = 0, basis = 1;
            for (int i = len - 1; i >= 0; i--)
            {
                num += (a[i] - '0') * basis;
                basis *= 10;
                if (t == digit)
                {
                    t = 0;
                    number.push_back(num);
                    num = 0;
                    basis = 1;
                }
                if (i == 0 && t != digit)
                {
                    number.push_back(num);
                }
                t++;
            }
        }
        while (number.size() > 1 && number[number.size() - 1] == 0) number.pop_back();
        (*this).check();
        if (number.size() == 1 && number[0] == 0) { sign = true; }
    }
    int2048::int2048(const int2048& a)
    {
        number.clear();
        number = a.number;
        sign = a.sign;
    }

    void int2048::read(const std::string& a)
    {
        number.clear();
        int len = a.size();
        int x = base, digit = 0;//digit记录基的位数
        while (x != 1)
        {
            digit++;
            x /= 10;
        }
        if (a[0] == '-')
        {
            sign = false;
            int t = 1, num = 0, basis = 1;
            for (int i = len - 1; i > 0; i--)
            {
                num += (a[i] - '0') * basis;
                basis *= 10;
                if (t == digit)
                {
                    t = 0;
                    number.push_back(num);
                    num = 0;
                    basis = 1;
                }
                if (i == 1 && t != digit)
                {
                    number.push_back(num);
                }
                t++;
            }
        }
        else
        {
            sign = true;
            int t = 1, num = 0, basis = 1;
            for (int i = len - 1; i >= 0; i--)
            {
                num += (a[i] - '0') * basis;
                //std::cout<<num<<"\n";
                basis *= 10;
                if (t == digit)
                {
                    t = 0;
                    number.push_back(num);
                    num = 0;
                    basis = 1;
                }
                if (i == 0 && t != digit)
                {
                    number.push_back(num);
                }
                t++;
            }
        }
        while (number.size() > 1 && number[number.size() - 1] == 0) number.pop_back();
        (*this).check();
    }
    void int2048::print()
    {
        int x = base, digit = 0;//digit记录基的位数
        while (x != 1)
        {
            digit++;
            x /= 10;
        }
        int len = number.size();
        if (sign == false)
        {
            if (number.size() == 1 && number[0] == 0) {}
            else
            {
                std::cout << '-';
            }
        }
        for (int i = len - 1; i >= 0; i--)
        {
            if (i != len - 1)
            {
                int num = 0;
                int tmp = number[i];
                while (tmp != 0)
                {
                    tmp /= 10;
                    num++;
                }
                for (int j = 1; j <= digit - num; j++)
                {
                    std::cout << 0;
                }
            }
            std::cout << number[i];
        }
    }

    bool reverse(bool a)
    {
        if (a == true)
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    void int2048::check()//防止出现-0
    {
        if (number.size() == 1 && number[0] == 0)
        {
            sign = true;
        }
    }

    std::vector<long long> absadd(const int2048& a, const int2048& b)
    {
        std::vector<long long>ans;
        int lena = a.number.size();
        int lenb = b.number.size();
        if (lena >= lenb)
        {
            ans = a.number;
            ans.push_back(0);
            for (int i = 0; i < lena; i++)
            {
                if (i < lenb)
                {
                    ans[i] += b.number[i];
                }
                if (ans[i] >= base)
                {
                    ans[i] -= base;
                    ans[i + 1] += 1;
                }
            }
            if (ans[lena] == 0)
            {
                ans.pop_back();
            }
        }
        else
        {
            ans = b.number;
            ans.push_back(0);
            for (int i = 0; i < lenb; i++)
            {
                if (i < lena)
                {
                    ans[i] += a.number[i];
                }
                if (ans[i] >= base)
                {
                    ans[i] -= base;
                    ans[i + 1] += 1;
                }
            }
            if (ans[lenb] == 0)
            {
                ans.pop_back();
            }
        }
        while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();
        return ans;
    }

    int2048& int2048::add(const int2048& a)
    {
        if (sign == a.sign)
        {
            number = absadd(*this, a);
        }
        else
        {
            int2048 tem = a;
            tem.sign = reverse(tem.sign);
            (*this).minus(tem);
        }
        (*this).check();
        return *this;
    }
    int2048 add(int2048 a, const int2048& b)
    {
        int2048 tem = a;
        tem.add(b);
        tem.check();
        return tem;
    }

    std::vector<long long> absminus(const int2048& a, const int2048& b)//默认a比b大
    {
        int lena = a.number.size();
        int lenb = b.number.size();
        std::vector<long long>ans = a.number;
        ans.push_back(0);
        for (int i = 0; i < lena; i++)
        {
            if (i < lenb)
            {
                ans[i] -= b.number[i];
            }
            if (ans[i] < 0)
            {
                ans[i] += base;
                ans[i + 1] -= 1;
            }
        }
        while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();//删除前导0
        return ans;
    }
    int2048& int2048::minus(const int2048& a)
    {
        int islarger = 0;//0代表一样大，1代表比a大，2代表比a小
        int len1 = number.size();
        int len2 = a.number.size();
        if (sign != a.sign)
        {
            number = absadd(*this, a);
        }
        else//符号相同
        {
            if (len1 == len2)
            {
                for (int i = len1 - 1; i >= 0; i--)
                {
                    if (number[i] > a.number[i])
                    {
                        islarger = 1;
                        break;
                    }
                    if (number[i] < a.number[i])
                    {
                        islarger = 2;
                        break;
                    }
                }
            }
            else if (len1 > len2)
            {
                islarger = 1;
            }
            else
            {
                islarger = 2;
            }

            if (islarger == 0)
            {
                number.clear();
                number.push_back(0);
                sign = true;
            }
            else if (islarger == 1)
            {
                number = absminus(*this, a);
            }
            else
            {
                number = absminus(a, *this);
                sign = reverse(sign);
            }
        }
        (*this).check();
        return *this;
    }
    int2048 minus(int2048 a, const int2048& b)
    {
        int2048 tem = a;
        tem.minus(b);
        tem.check();
        return tem;
    }

    int2048 int2048::operator+() const
    {
        return *this;
    }
    int2048 int2048::operator-() const
    {
        int2048 tem = *this;
        tem.sign = reverse(tem.sign);
        tem.check();
        return tem;
    }

    int2048& int2048::operator=(const int2048& a)
    {
        number = a.number;
        sign = a.sign;
        return *this;
    }

    int2048& int2048::operator+=(const int2048& a)
    {
        (*this).add(a);
        (*this).check();
        return *this;
    }
    int2048 operator+(int2048 a, const int2048& b)
    {
        return add(a, b);
    }

    int2048& int2048::operator-=(const int2048& a)
    {
        (*this).minus(a);
        (*this).check();
        return *this;
    }
    int2048 operator-(int2048 a, const int2048& b)
    {
        return minus(a, b);
    }

    int2048& int2048::operator*=(const int2048& a)
    {
        if (sign == a.sign)
        {
            sign = true;
        }
        else
        {
            sign = false;
        }
        int len = number.size();
        int lena = a.number.size();
        std::vector<long long>ans(len + lena + 1, 0);
        for (int i = 0; i < len; i++)
        {
            for (int j = 0; j < lena; j++)
            {
                ans[i + j] += number[i] * a.number[j];
            }
        }
        for (int k = 0; k < len + lena; k++)
        {
            if (ans[k] >= base)
            {
                ans[k + 1] += ans[k] / base;
                ans[k] = ans[k] % base;
            }
        }
        while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();//删除前导0
        number = ans;
        (*this).check();
        return *this;
    }
    int2048 operator*(int2048 a, const int2048& b)
    {
        a *= b;
        return a;
    }

    int2048 multi(int2048 x, long long a)//多精度乘单精度，比多精度乘上多精度要快很多
    {
        long long len = x.number.size();
        std::vector<long long> ans(len + 1, 0);
        for (int i = 0; i < len; i++)
        {
            ans[i] += x.number[i] * a;
            if (ans[i] >= base)
            {
                ans[i + 1] += ans[i] / base;
                ans[i] %= base;
            }
        }
        while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();//删除前导0
        x.number = ans;
        return x;
    }

    int2048& int2048::operator/=(const int2048& a)
    {
        int len = number.size();
        int lena = a.number.size();
        int2048 tem1 = *this;
        int2048 tem2 = a;
        tem1.sign = tem2.sign = true;
        if (sign == a.sign)
        {
            sign = true;
        }
        else
        {
            sign = false;
        }

        if (tem2 > tem1)
        {
            number.clear();
            number.push_back(0);
            if (sign == false && tem1 != 0)
            {
                *this -= 1;
            }
        }
        else if (tem2 == tem1)
        {
            number.clear();
            number.push_back(1);
        }
        else
        {
            std::vector<long long> ans(len - lena + 1, 0);
            for (int i = len - lena; i >= 0; i--)//第二次写的除法
            {
                int2048 tmp = tem2;
                tmp.number.insert(tmp.number.begin(), i, 0);
                int l = 0, r = base - 1, mid, note = 0;
                while (l < r)
                {
                    mid = (l + r + 1) / 2;
                    if (multi(tmp, mid) <= tem1)
                    {
                        l = mid;
                        note = (mid > note) ? mid : note;
                    }
                    else
                    {
                        r = mid - 1;
                    }
                }
                tem1 -= tmp * note;
                ans[i] = note;
            }
            while (ans.size() > 1 && ans[ans.size() - 1] == 0) ans.pop_back();//删除前导0
            number = ans;
            if (tem1.number.size() == 1 && tem1.number[0] == 0) {}
            else
            {
                if (sign == false)
                {
                    *this -= 1;
                }
            }
        }
        (*this).check();
        return *this;
    }
    int2048 operator/(int2048 a, const int2048& b)
    {
        a /= b;
        return a;
    }

    int2048& int2048::operator%=(const int2048& a)
    {
        int2048 tem = (*this) / a;
        *this = *this - a * tem;
        (*this).check();
        return *this;
    }
    int2048 operator%(int2048 a, const int2048& b)
    {
        a %= b;
        return a;
    }

    std::istream& operator>>(std::istream& is, int2048& a)
    {
        std::string s;
        is >> s;
        a.read(s);
        return is;
    }
    std::ostream& operator<<(std::ostream& os, const int2048& a)
    {
        int x = base, digit = 0;//digit记录基的位数
        while (x != 1)
        {
            digit++;
            x /= 10;
        }
        if (a.sign == false)
        {
            os << "-";
        }
        for (int i = a.number.size() - 1; i >= 0; i--)
        {
            if (i != a.number.size() - 1)
            {
                int num = 1;
                int tmp = a.number[i] / 10;
                while (tmp != 0)
                {
                    tmp /= 10;
                    num++;
                }
                //std::cout<<" "<<digit-num<<" ";
                for (int j = 1; j <= digit - num; j++)
                {
                    os << 0;
                }
            }
            os << a.number[i];
        }
        return os;
        /*int x=base,digit=0;//digit记录基的位数
        while(x!=1)
        {
            digit++;
            x/=10;
        }
        int len=number.size();
        if(sign==false)
        {
            if(number.size()==1&&number[0]==0){}
            else
            {
                std::cout << '-';
            }
        }
        for(int i=len-1;i>=0;i--)
        {
            if(i!=len-1)
            {
                int num=0;
                int tmp=number[i];
                while(tmp!=0)
                {
                    tmp/=10;
                    num++;
                }
                for(int j=1;j<=digit-num;j++)
                {
                    std::cout<<0;
                }
            }
            std::cout<<number[i];
        }*/
    }

    bool operator==(const int2048& a, const int2048& b)
    {
        if (a.number.size() == 1 && a.number[0] == 0 && b.number.size() == 1 && b.number[0] == 0)
        {
            return true;
        }
        else
        {
            if (a.sign != b.sign)
            {
                return false;
            }
            else
            {
                int len_a = a.number.size();
                int len_b = b.number.size();
                if (len_a != len_b)
                {
                    return false;
                }
                else
                {
                    for (int i = 0; i < len_a; i++)
                    {
                        if (a.number[i] != b.number[i])
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
    bool operator!=(const int2048& a, const int2048& b)
    {
        if (a == b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator<(const int2048& a, const int2048& b)
    {
        int len_a = a.number.size();
        int len_b = b.number.size();
        if (a.sign == true)
        {
            if (b.sign == false)
            {
                return false;
            }
            else
            {
                if (len_a > len_b)
                {
                    return false;
                }
                else if (len_a < len_b)
                {
                    return true;
                }
                else
                {
                    for (int i = len_a - 1; i >= 0; i--)
                    {
                        if (a.number[i] < b.number[i])
                        {
                            return true;
                        }
                        else if (a.number[i] > b.number[i])
                        {
                            return false;
                        }
                    }
                    return false;
                }
            }
        }
        else
        {
            if (b.sign == true)
            {
                return true;
            }
            else
            {
                if (len_a > len_b)
                {
                    return true;
                }
                else if (len_a < len_b)
                {
                    return false;
                }
                else
                {
                    for (int i = len_a - 1; i >= 0; i--)
                    {
                        if (a.number[i] < b.number[i])
                        {
                            return false;
                        }
                        else if (a.number[i] > b.number[i])
                        {
                            return true;
                        }
                    }
                    return false;
                }
            }
        }
    }
    bool operator>(const int2048& a, const int2048& b)
    {
        if (a < b || a == b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator<=(const int2048& a, const int2048& b)
    {
        if (a > b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    bool operator>=(const int2048& a, const int2048& b)
    {
        if (a < b)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
} // namespace sjtu