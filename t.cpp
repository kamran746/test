
#include <iostream>
#include <regex>
#include <memory>

using namespace std;


string remove_comments(const string& fname)
{
    char buf[1024];

    string cmd = "gcc -fpreprocessed -dD -E " + fname;
    string str;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(),"r"),pclose);
    if(pipe)
    {
        while(fgets(buf,sizeof(buf),pipe.get()) != nullptr)
            str += buf;
    }
    else
        throw("error in execting comand");
    return str;
}

string remove_body(const char* src)
{
    string str;
    while (*src++)
    {
        if(*src == '{')
        {
            str += '{';
            int cnt = 1;
            int i = 1;
            while(*(src + i))
            {
                if(*(src + i) == '{')
                    ++cnt;
                else if(*(src + i) == '}')
                    --cnt;
                ++i;
                if(cnt == 0)
                {
                    src += i;
                    str += '}';
                    break;
                }
            }
        }
        else
        {
            str += *src;
        }
        
    }

    return str;
    
}

#include <fstream>
string readfile(const string& path)
{

	ifstream infile(path);
	string str;
	if(infile.is_open())
	{
		infile.seekg(0,ios::end);
		int end = infile.tellg();
		cout << "len = " << end << endl;
		char * buf = new char[end + 1];
		infile.seekg(0,ios::beg);

		infile.read(buf,end);
		buf[end+1] = 0;
		str = buf;
		delete[] buf;
	}

	return str;
}

struct mystruct
{
    int n;
    char c;
};




int main(int argc, char *argv[])
{

    mystruct f={
        .n = 9
        };
        
    string s1 = remove_comments("/home/mch/prjs/test/mmtmp.c");

    string str = remove_body(s1.c_str());


        cout  << " start " << endl;
   
    //regex rg(R"S(^\s*(?:(?:inline|static)\s+){0,2}(?!else|typedef|return)\w+\s+\*?\s*(\w+)\s*\([^0]+\)\s*;?)S");

    //string str =    "void func1(pte_t pte);""void func2(pte_t pte,ddd , sdsfd);";
    
    //string str = "int f\n( int fff) ; do {} while(0)" "#define flush_tlb_fix_spurious_fault(vma, address) do { } while (0) #define mk_pmd(page, pgprot)   pfn_pmd(page_to_pfn(page), (pgprot))";

// 	regex rg(R"S(\w+\s*\(\w+\s+\w+\)\;*)S");
// 	regex rg(R"S(\w*\s*\(\w*\s*\w*\s*\w*(\,\w*\s*\w*\s*\w*)*\)\;*)S");
// 	regex rg(R"S(\w*\s*\((\s*\w*\**\,*)*\))S");
// 	regex rg(R"S(\w+\s+\w+\s*\([^)]*\)\s*(\{|\;))S");
 	regex rg(R"S(\w+\s+\w+\s*\([^)]*\))S");


	auto words_begin = std::sregex_iterator(str.begin(), str.end(), rg);
    
	auto words_end = std::sregex_iterator();


    for (std::sregex_iterator i = words_begin; i != words_end; ++i) 
	{
        std::smatch match = *i;                                                 
        std::string match_str = match.str(); 
        std::cout << match_str << '\n';
    }  	




	return 0;

}
