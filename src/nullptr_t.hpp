/*
 * nullptr_t.hpp
 *
 *  Created on: 31.05.2013
 *      Author: Christoph Grundmann
 */

#ifndef NULLPTR_T_HPP_
#define NULLPTR_T_HPP_

const
class nullptr_t
{
public:
    template<class T>
    operator T*() const
    { return 0; }

    template<class C, class T>
    operator T C::*() const
    { return 0; }

private:
    void operator&() const;

} nullptr = {};


#endif /* NULLPTR_T_HPP_ */
