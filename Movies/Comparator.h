#pragma once
#include "Movie.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

template <typename Type>
class Comparator
{
public:
    virtual bool compare(Type elem1, Type elem2) = 0;
};


template <typename Type>
class ComparatorAscendingByYear : public Comparator<Type>
{
public:
    bool compare(Type elem1, Type elem2) override;
};

template <typename Type>
class ComparatorDescendingByLikes : public Comparator<Type>
{
public:
    bool compare(Type elem1, Type elem2) override;
};

template <typename Type>
inline bool ComparatorAscendingByYear<Type>::compare(Type elem1, Type elem2)
{
    return elem1.GetYear() < elem2.GetYear();
}

template <typename Type>
inline bool ComparatorDescendingByLikes<Type>::compare(Type elem1, Type elem2)
{
    return elem1.GetLikes() > elem2.GetLikes();
}


template <typename Type>
void genericSort(std::vector<Type>& v, Comparator<Type>* cmp)
{
    bool sorted = true;

    do
    {
        sorted = true;

        for (int i = 0; i < v.size() - 1; i++)
        {
            if (!cmp->compare(v[i], v[i + 1]))
            {
                std::swap(v[i], v[i + 1]);
                sorted = false;
            }
        }
    } while (!sorted);

}



void testSort()
{
    std::vector<Movie> general;
    general.push_back(Movie("Shutter_Island", "psychological", 2019, 1009, "https://google.ro"));
    general.push_back(Movie("Anabelle", "Horror", 2016, 10, "https://google.ro"));
    general.push_back(Movie("Mamma mia", "musical", 2013, 1345, "https://google.ro"));

    std::vector<Movie> year{ general };
    std::vector<Movie> likes{ general };

    Comparator<Movie>* cmpSize = new ComparatorAscendingByYear<Movie>{};
    Comparator<Movie>* cmpPrice = new ComparatorDescendingByLikes<Movie>{};

    genericSort<Movie>(year, cmpSize);
    genericSort<Movie>(likes, cmpPrice);

    assert(year[0].GetYear() == 2013);
    assert(year[1].GetYear() == 2016);
    assert(year[2].GetYear() == 2019);


    assert(likes[0].GetLikes() == 1345);
    assert(likes[1].GetLikes() == 1009);
    assert(likes[2].GetLikes() == 10);

    delete cmpSize;
    delete cmpPrice;
}