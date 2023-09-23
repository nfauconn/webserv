#ifndef ACONTEXT_HPP
# define ACONTEXT_HPP

# include <cstdlib>

# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include <map>
# include <vector>

#include "print.hpp"

class LocationContext;

class AContext {

	public:
		AContext(AContext const& rhs);
		AContext&	operator=(AContext const& rhs);
		AContext(std::string const& conf_filename);
		~AContext();

		std::vector<AContext> const &		getContexts(void) const;
		std::string const &					getConfFileName(void) const;
		size_t								getLinesRead(void) const;
		bool								getAutoindex() const;
		bool								getCgi() const;
		size_t								getMaxBodySize() const;
		std::string const&					getRoot() const;
		std::map<int, std::string> const&	getErrorPages() const;
		std::vector<std::string> const&		getIndex() const;
		std::vector<std::string> const&		getAuthorizedMethods() const;

		void	setAutoindex(bool autoindex);
		void	setCgi(bool cgi);
		void	setMaxBodySize(size_t size);
		void	setRoot(std::string const& root);
		void	addErrorPage(int code, std::string const& path);
		void	setErrorPage(std::map<int, std::string> const& errorPages);
		void	setIndex(std::vector<std::string> const& index);
		void	setAuthorizedMethods(std::vector<std::string> const& authorizedMethods);
		void	parse();

	protected:
		void	parseContext(std::stringstream& stream);
		void	parseServerLocationContext(std::stringstream& stream);

		typedef void (AContext::*ParserFunction)(std::string const&);
    	typedef std::pair<std::string, AContext::ParserFunction> DirectivePair;
		typedef std::map<std::string, AContext::ParserFunction> DirectiveMap;

		void	parseAutoindex(std::string const& line);
		void	parseCgi(std::string const& line);
		void 	parseMaxBodySize(std::string const& line);
		void	parseRoot(std::string const& line);
		void	parseErrorPage(std::string const& line);
		void	parseIndex(std::string const& line);
		void	parseAuthorizedMethods(std::string const& line);

		// UTILS
		bool	isDirective(std::string const& line) const;
		bool	isCommentOrEmptyLine(std::string const& line) const;
		bool	isEndOfScope(std::string const& line) const;
		void	isValidIPv4(std::string const& str) const;
		void	isValidIPv6(std::string const& str) const;
		void 	trimAndReplaceWhitespaces(std::string& input);
		void	buildAndThrowParamError(std::string const& line) const;

	private:
		AContext();

		size_t						_linesRead;
		std::string		 			_confFilename;
		std::vector<AContext>		_contexts;
		bool						_autoindex;
		bool						_cgi;
		size_t						_maxBodySize;
		std::string					_root;
		std::map<int, std::string>	_errorPages;
		std::vector<std::string>	_index;
		std::vector<std::string>	_authorizedMethods;

	
	public:
		class Error : public std::exception {
			public:
				Error(std::string msg);
				virtual ~Error() throw();
				virtual const char* what() const throw();
			protected:
				std::string _msg;
		};

		class InvalidParam : public Error {
			public:
				InvalidParam(std::string const& err, AContext const& p);
				virtual ~InvalidParam() throw();
		};

};

std::ostream &	operator<<(std::ostream & o, AContext const & cc);

#endif