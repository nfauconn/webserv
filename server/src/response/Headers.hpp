#ifndef HEADERS_HPP
# define HEADERS_HPP

# include "AResponse.hpp"

class Headers : public AResponse {
	
	public:
		Headers();
		Headers(std::string const &);
		Headers(Headers const & src);
		~Headers();
	
		Headers &		operator=(Headers const & rhs);

		void		setContentLength(size_t const & contentLength);
		size_t		getContentLength() const;

		void		build();

	private:
		size_t	_contentLength;	
};

#endif