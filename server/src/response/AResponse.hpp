#ifndef ARESPONSE_HPP
# define ARESPONSE_HPP

# include <iostream>
# include <string>
# include <sstream>

# include "macros.hpp"

class AResponse {

	public:
		AResponse();
		AResponse(std::string const &);
		AResponse(AResponse const & src);
		virtual ~AResponse();

		AResponse &		operator=(AResponse const & rhs);

		void			setMessage(std::string const & message);
		std::string		getMessage() const;

		virtual void	build() = 0;
	
	public:
		std::string _message;
};

#endif