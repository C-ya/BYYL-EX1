#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cctype>
#include <algorithm>
#include <iterator>

using namespace std;

string Tag[3] = {"var", "const", "procedure"}; //以此判断是否为定义标识符语句
string Tags[1024] = {""};                      //标识符数组
string str[1024] = {""};                       //语句存放
int Count[1024] = {0};                         //计数数组

//初始化函数
void init(int len, int num)
{
    for (int i = 0; i < len; i++)
        str[i].clear();
    for (int i = 0; i < num; i++)
    {
        Tags[i].clear();
        Count[i] = 0;
    }
}

//按行读取文件存入str数组，返回文件行数
int rFile(char file[])
{
    cout << file << endl;
    string s;
    int l = 0;
    ifstream inf;
    inf.open(file);
    while (getline(inf, s)) //逐行读取inf中的文件信息
    {
        //大写字母转换成小写
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        //去掉注释
        if (s[0] == '{')
            continue;
        //去掉首尾空格
        size_t n = s.find_last_not_of(" \t");
        if (n != string::npos)
        {
            s.erase(n + 1, s.size() - n);
        }
        n = s.find_first_not_of(" \t");
        if (n != string::npos)
        {
            s.erase(0, n);
        }
        str[l++] = s;
    }
    //返回文件行数
    return l;
    inf.close();
}

//清除特殊符号
void Clear(string str[], int len)
{
    for (int i = 0; i < len; i++)
    {
        //
        for (int j = 0; j < str[i].length(); j++)
        {
            char ch = str[i][j];
            //检测非空格、字母、数字的可打印字符，转换成空格
            if (ispunct(ch))
                str[i][j] = ' ';
        }
        //去掉尾部空格
        size_t n = str[i].find_last_not_of(" \t");
        if (n != string::npos)
        {
            str[i].erase(n + 1, str[i].size() - n);
        }
    }
}

//裁剪函数寻找标识符，返回标识符个数
int Cut(string str[], int len)
{
    int num = 0;
    for (int i = 0; i < len; i++)
    { //将字符串分割成字符串数组
        int s = 0, flag = 0;
        string head[1024] = {""};
        for (int j = 0; j < str[i].length(); j++)
        {
            if (str[i][j] == ' ' && str[i][j + 1] != ' ')
            {
                s++;
                continue;
            }
            if (str[i][j] == ' ')
            {
                continue;
            }
            //防止多个空格作为分隔符
            head[s] += str[i][j];
        }
        //如果是标识符，则存入数组，标识符数量加一
        for (int k = 0; k < 3; k++)
        {
            if (head[0] == Tag[k])
            {
                flag = 1;
                for (int t = 1; t <= s; t++)
                {
                    if (head[t][0] >= 'a' && head[t][0] <= 'z')
                    {
                        Tags[num] = head[t];
                        Count[num] += 1;
                        num++;
                    }
                }
                break;
            }
        }

        //非定义语句，查找标识符
        if (flag != 1)
        {
            for (int k = 0; k <= s; k++)
            {
                for (int t = 0; t < num; t++)
                {
                    if (head[k] == Tags[t])
                        Count[t] += 1;
                }
            }
        }
    }
    //输出标识符个数和出现次数
    cout << "标识符个数：" << num << endl;
    for (int m = 0; m < num; m++)
    {
        cout << Tags[m] << "----> ";
        cout << Count[m] << endl;
    }
    //返回标识符个数
    return num;
}

//写操作函数，将结果打印到outtest.txt文件中
void pFile(int num)
{
    ofstream outf;
    outf.open(".//outtest.txt");
    for (int i = 0; i < num; i++)
        outf << "(" << Tags[i] << ": " << Count[i] << ")" << '\n';
    outf.close();
}

//执行函数
void Exe(char file[])
{
    int len = rFile(file);
    Clear(str, len);
    cout << "按行读取并处理后的字符数组：" << endl;
    for (int i = 0; i < len; i++)
        cout << str[i] << endl;
    int num = Cut(str, len);
    pFile(num);
    init(len, num);
}

int main()
{
    int n;
    char file[] = "";
    cout << endl << "请输入数字（1-5）进行文件测试，0退出：";
    cin >> n;
    while (n != 0)
    {
        switch (n)
        {
        case 1:
        {
            strcpy(file, ".//test1.txt");
            Exe(file);
            break;
        }
        case 2:
        {
            strcpy(file, ".//test2.txt");
            Exe(file);
            break;
        }
        case 3:
        {
            strcpy(file, ".//test3.txt");
            Exe(file);
            break;
        }
        case 4:
        {
            strcpy(file, ".//test4.txt");
            Exe(file);
            break;
        }
        case 5:
        {
            strcpy(file, ".//test5.txt");
            Exe(file);
            break;
        }
        default:
        {
            break;
        }
        }
        cout << endl << "请输入数字（1-5）进行文件测试，0退出：";
        cin >> n;
    }
    return 0;
}