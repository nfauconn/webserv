#ifndef BODY_HPP
# define BODY_HPP

# include "AResponse.hpp"

class Body : public AResponse {
	
	public:
		Body();
		Body(std::string const &);
		Body(Body const & src);
		~Body();
	
		Body &		operator=(Body const & rhs);

		void		build();
};

#endif