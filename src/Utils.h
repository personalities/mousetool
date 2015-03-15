#ifndef UTILS_H_
#define UTILS_H_

namespace uti {
	enum {
		//if set, handle quotes correctly
		TOK_HANDLE_QUOTES=1,
			
			//if set, don't elide tokens. that is, every occurrence of a seperator
			//indicates a new token. this allows empty tokens. for example:
			//	"fred,,,jim"	= {"fred","","","jim"} with TOK_DONT_ELIDE_TOKENS;
			//					= {"fred","jim"} without TOK_DONT_ELIDE_TOKENS.
			//
			//probably rather annoying if the seperators are whitespace.
			TOK_DONT_ELIDE_TOKENS=2,
	};
	
	void TokenizeString(const std::string &source,const std::string &seperators,
		std::vector<std::string> &tokensOutput,unsigned flags=0);

	void dprintf(const char *fmt,...);

	struct string_lessthan_nocase:
	public std::less<std::string>
	{
		inline bool operator()(const std::string &lhs, const std::string &rhs) const {
			return stricmp(lhs.c_str(),rhs.c_str())<0;
		}
	};
}


#ifdef _DEBUG
# define MTASSERT_MSG(X,Y,Z) (uti::dprintf("%s(%u): assert failed: %s\n",X,#Y,#Z),true)
# define MTASSERT(X) if(!(X)&&MTASSERT_MSG(__FILE__,__LINE__,X)) __asm int 3
#else
# define MTASSERT(X)
#endif

#endif