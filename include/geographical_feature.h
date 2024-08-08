#ifndef GEOGRAPHICAL_FEATURE_H
#define GEOGRAPHICAL_FEATURE_H

#include <string>

class GeographicalFeature {
public:
    GeographicalFeature(const std::string &type, const std::string &details, const std::string &area);

    std::string getType() const;
    std::string getDetails() const;
    std::string getArea() const;

private:
    std::string type;
    std::string details;
    std::string area;
};

#endif // GEOGRAPHICAL_FEATURE_H
