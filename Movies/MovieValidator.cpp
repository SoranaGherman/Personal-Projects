#include "MovieValidator.h"

using namespace std;

ValidationException::ValidationException(std::string _message) : message{ _message }
{
}

std::string ValidationException::getMessage() const
{
	return this->message;
}


ValidationExceptionInherited::ValidationExceptionInherited(std::string _message) : message{ _message }
{
}

const char* ValidationExceptionInherited::what() const noexcept
{
	return message.c_str();
}


void MovieValidator::validate(const Movie& s)
{
	string errors;
	if (s.GetTitle().size() < 2)
		errors += string("The movie title must have at least two characters!\n");

	if (s.GetGenre().size() < 2)
		errors += string("The movie genre must have at least two characters!\n");

	if ((int)s.GetLikes() < 0)
		errors += string("The number of likes has to be a natural number!\n");

	if ((int)s.GetYear() < 1800 || (int)s.GetYear() > 2022)
		errors += string("The year of release has to be greater than 1800 and smaller than 2022!\n");

	if (errors.size() > 0)
		throw ValidationException(errors);

	/*if (errors.size() > 0)
		throw ValidationExceptionInherited(errors);*/
}
