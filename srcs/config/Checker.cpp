/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Checker.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: athierry <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 19:20:13 by athierry          #+#    #+#             */
/*   Updated: 2023/08/08 19:28:03 by athierry         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_HPP
# define CHECKER_HPP

enum	nodes{
	ROOT = 0,
	SERVER = 1,
	LOCATION,
	COUNT
};

const std::string	depth[] = {
	"root",
	"server",
	"location",
	""
};

typedef struct	s_checker{
	std::string	name;
	std::string	defaultValue;
	bool		mandatory;
	bool		possible;
	bool		isNode;
	bool		isDirective;
	bool		isMultiple;
	bool		hasUri;
}				t_checker;

# define KEYWORDS 13

const t_keywords keywords[COUNT][KEYWORDS] = {
	/*.....................................ROOT CONTEXT..........................................*/
{	/*.Keyword..................Default.........Manda...Possi...Direc...Bloc....URI.....Multi....................*/
	{ "server",					"",				true,	true,	false,	true,	false,	false	}, //.Sets configuration for a virtual server...............
	{ "index",					"",				false,	true,	true,	false,	false,	true	}, //.Defines files that will be used as an index...........
	{ "root",					"",		 		false,	true,	true,	false,	false,	false	}, //.Sets the root directory for requests..................
	{ "cgi",					"off",		 	true,	true,	true,	false,	false,	false	}, //.Defines whether response should be construct from CGI.
	{ "",						"",				false,	false,	false,	false,	false,	false	}, //.Default settings if keyword was not found.............
},
	/*.....................................SERVER CONTEXT........................................*/
{	/*.Keyword..................Default.........Manda...Possi...Direc...Bloc....URI.....Multi....................*/
	{ "location",				"",				true,	true,	false,	true,	true,	false	}, //.Sets configuration depending on a request URI.........
	{ "root",					"",				false, 	true,	true,	false,	false,	false	}, //.Sets the root directory for requests..................
	{ "listen",					"0.0.0.0:8080",	true, 	true,	true,	false,	false,	false	}, //.Sets address:port IP, or the UNIX-domain socket path..
	{ "server_name",			"webserv-42", 	true,	true,	true,	false,	false,	false	}, //.Sets names of a virtual server........................
	{ "index",					"",			 	false,	true,	true,	false,	false,	true	}, //.Defines files that will be used as an index...........
	{ "autoindex",				"off",		 	true,	true,	true,	false,	false,	false	}, //.Defines whether autoindex should be generated.........
	{ "client_max_body_size",	"1m",		 	true,	true,	true,	false,	false,	false	}, //.Defines a max size for client requests body...........
	{ "error_page",				"default",	 	true,	true,	true,	false,	false,	true	}, //.Determines the paths to error pages...................
	{ "allowed_methods",		"default",		true,	true,	true,	false,	false,	true	}, //.Determines allowed http methods...........
	{ "cgi",					"off",		 	true,	true,	true,	false,	false,	false	}, //.Defines whether response should be construct from CGI.
	{ "rewrite",				"",		 	 	false,	true,	true,	false,	false,	true	}, 
	{ "upload_folder",			"."	,	 	 	true,	true,	true,	false,	false,	false	}, //.Define default file upload folder.....................
	{ "",						"",				false,	false,	false,	false,	false,	false	}, //.Default settings if keyword was not found.............
},
	/*....................................LOCATION CONTEXT.......................................*/
{	/*.Keyword..................Default.........Manda...Possi...Direc...Bloc....URI.....Multi....................*/
	{ "root",					"",				false,	true,	true,	false,	false,	false	}, //.Sets the root directory for requests..................
	{ "index",					"index.html",	true,	true,	true,	false,	false,	true	}, //.Defines files that will be used as an index...........
	{ "server_name",			"",		 		false,	true,	true,	false,	false,	false	}, //.Sets names of a virtual server........................
	{ "autoindex",				"off",			true,	true,	true,	false,	false,	false	}, //.Defines whether autoindex should be generated.........
	{ "client_max_body_size",	"1m",		 	true,	true,	true,	false,	false,	false	}, //.Defines a max size for client requests body...........
	{ "error_page",				"default",		true,	true,	true,	false,	false,	true	}, //.Determines the paths to error pages...................
	{ "allowed_methods",		"default",	 	true,	true,	true,	false,	false,	true	}, //.Determines allowed http methods...........
	{ "cgi",					"off",			true,	true,	true,	false,	false,	false	}, //.Defines whether response should be construct from CGI.
	{ "rewrite",				"",				false,	true,	true,	false,	false,	true	}, 
	{ "upload_folder",			".",	 		true,	true,	true,	false,	false,	false	}, // Define default file upload folder
	{ "",						"",				false,	false,	false,	false,	false,	false	}, //.Default settings if keyword was not found.............
},

}; 

#endif
