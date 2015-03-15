#include "stdafx.h"

void uti::TokenizeString(const std::string &source,const std::string &seperators,
	std::vector<std::string> &tokensOutput,unsigned flags)
{
	static const char QUOTE_CHAR='"';
	std::vector<std::string>::iterator currentToken;
	std::string::const_iterator currentChar;
	bool inQuotes=false;
	bool handleQuotes=!!(flags&TOK_HANDLE_QUOTES);
	
	if(handleQuotes&&seperators.find_first_of(QUOTE_CHAR)!=std::string::npos) {
		handleQuotes=false;
	}
	tokensOutput.clear();
	currentToken=tokensOutput.end();
	for(currentChar=source.begin();currentChar!=source.end();currentChar++) {
		if(handleQuotes&&*currentChar==QUOTE_CHAR) {
			inQuotes=!inQuotes;
			continue;
		}
		if(!inQuotes&&seperators.find_first_of(*currentChar)!=std::string::npos) {
			// this is a seperator. 
			if(flags&TOK_DONT_ELIDE_TOKENS) {
				if(currentToken==tokensOutput.end()) {
					tokensOutput.push_back("");
				}
			}
			currentToken=tokensOutput.end();
			continue;
		}
		// this is not a seperator.
		if(currentToken==tokensOutput.end()) {
			// This was a call to
			//		iterator insert(iterator it, const T& x = T());
			// like this:
			//		currentToken=tokensOutput.insert(tokensOutput.end());
			// but VC++ didn't like it...
			currentToken=tokensOutput.insert(tokensOutput.end(),std::string());
		}
		currentToken->insert(currentToken->end(),*currentChar);
	}
}

static void uti::dprintf(const char *fmt,...) {
	char tmpbuf[256];
	va_list v;
	va_start(v,fmt);
	_vsnprintf(tmpbuf,sizeof tmpbuf,fmt,v);
	va_end(v);
	OutputDebugStringA(tmpbuf);
}
