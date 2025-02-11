#ifndef DRAWABLELIST_HPP
#define DRAWABLELIST_HPP

#include "drawable.hpp"

#include <memory>
#include <vector>

class drawableList : public drawable
{
public:
    std::vector<std::shared_ptr<drawable>> dList;
    
    drawableList(){}
    drawableList(std::shared_ptr<drawable> object) {Add(object);}

    void Add(std::shared_ptr<drawable> object)
    {
        dList.push_back(object);
    }

    void Clear() {dList.clear();}

    bool hit( const ray& r, 
              range tRange,
              hitData& hitInfo) const override
              {
                hitData info;
                bool hitSmth = false;
                auto currentClosest = tRange.max;

                for(const auto& drawable : dList)
                {
                    if(drawable->hit(r, range(tRange.min, currentClosest), info))
                    {
                        hitSmth = true;
                        currentClosest = info.t;
                        hitInfo = info;
                    }
                }

                return hitSmth;
              }
};

#endif