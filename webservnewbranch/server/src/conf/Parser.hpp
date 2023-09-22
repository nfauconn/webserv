#ifndef PARSER_HPP
# define PARSER_HPP

# include <cstdlib>

# include <fstream>
# include <iostream>
# include <sstream>
# include <string>

# include "ServerContext.hpp"
# include "LocationContext.hpp"

class ServerContext;
class LocationContext;

class Parser {

	public:
		Parser(Parser const& rhs);
		Parser&	operator=(Parser const& rhs);
		Parser(std::string const& conf_filename);
		~Parser();

		std::vector<ServerContext> const &	getServerContexts(void) const;
		std::string const &					getConfFileName(void) const;
		size_t								getLinesRead(void) const;

		void	parse();

	private:
		Parser();

		size_t									_linesRead;
		std::string		 						_confFilename;
		std::vector<ServerContext>				_serverContexts;
		std::map<std::string, LocationContext>	_locations;

		// ::::::::::::::::::::::::::::::::::::::::::::::::Server context
		void	parseServerContext(std::stringstream& stream);
//		void	parseServerLocationContext(std::stringstream& stream, ServerContext& serverContext);

		typedef void (Parser::*ServerDirectiveParsers)(std::string const&, ServerContext&);
    	typedef std::pair<std::string, Parser::ServerDirectiveParsers> ServerDirectivePair;
		typedef std::map<std::string, Parser::ServerDirectiveParsers> ServerDirectiveMap;

		void	parseAutoindex(std::string const& line, ServerContext& serverContext);
		void	parseListen(std::string const& line, ServerContext& serverContext);
		void	parseIndex(std::string const& line, ServerContext& serverContext);
		void	parseServerName(std::string const& line, ServerContext& serverContext);


		// ::::::::::::::::::::::::::::::::::::::::::::::::Location context
		void	parseLocationContext(std::stringstream& stream);


		// ::::::::::::::::::::::::::::::::::::::::::::::::Common
		template <typename Context>
		using CommonDirectiveParsers = void (Parser::*)(std::string const&, Context&);
		template <typename Context>
		using CommonDirectivePair = std::pair<std::string, CommonDirectiveParsers<Context>>;
		template <typename Context>
		using CommonDirectiveMap = std::map<std::string, CommonDirectiveParsers<Context>>;

		template<typename Context>
		void	parseCgi(std::string const& line, Context& context);
		template<typename Context>
		void 	parseMaxBodySize(const std::string& line, Context& context);
		template<typename Context>
		void	parseRoot(std::string const& line, Context& context);
		template<typename Context>
		void	parseErrorPage(std::string const& line, Context& context);
		template<typename Context>
		void	parseAuthorizedMethods(const std::string& line, Context& context);

		// ::::::::::::::::::::::::::::::::::::::::::::::::::::::utils
		bool	isDirective(std::string const& line) const;
		bool	isCommentOrEmptyLine(std::string const& line) const;
		bool	isEndOfScope(std::string const& line) const;
		void	isValidIPv4(std::string const& str) const;
		void	isValidIPv6(std::string const& str) const;
		void 	trimAndReplaceWhitespaces(std::string& input);
		void	buildAndThrowParamError(std::string const& line) const;

	
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
				InvalidParam(std::string const& err, Parser const& p);
				virtual ~InvalidParam() throw();
		};

};

#endif