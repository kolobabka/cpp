#include <iostream>
#include "geom.h"

int main ()
{
    my_geom::Triangle tr (my_geom::Point (0, 0), my_geom::Point (1, 1), my_geom::Point (-1, 1));
    my_geom::Square sq (my_geom::Point (2, 2), 3);
    my_geom::Circle cir (my_geom::Point (0, 0), 1);

    my_geom::StringVisitor visitor;
    tr.accept (visitor);
    sq.accept (visitor);
    cir.accept (visitor);

    std::cout << visitor.get_result ();

    return 0;
}

