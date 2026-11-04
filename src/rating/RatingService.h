#ifndef GLADIATORS_RATINGSERVICE_H
#define GLADIATORS_RATINGSERVICE_H

#include <qlist.h>
#include "../entities/Gladiator.h"

class RatingService {
public:
    RatingService() = delete;

    static QList<Gladiator> getTop(int count);
};


#endif //GLADIATORS_RATINGSERVICE_H