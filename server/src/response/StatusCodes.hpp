#ifndef STATUSCODES_HPP
# define STATUSCODES_HPP

# include "AFile.hpp"

class StatusCodes : public AFile {
	public:
		StatusCodes();
		StatusCodes(std::string const&);
		~StatusCodes();

		std::string const& getStatusMessage(std::string const&) const;
};

#endif