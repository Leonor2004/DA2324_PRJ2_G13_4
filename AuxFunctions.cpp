#include "AuxFunctions.h"
#include <cmath>

AuxFunctions::AuxFunctions() = default;

void AuxFunctions::test() {
    for (auto a : csvInfo::edgesGraph.getVertexSet()){
        cout << a->getInfo() << endl;
        for(auto b : a->getAdj()) {
            cout << "Origem: " << b->getOrig()->getInfo() << "- Destino: " << b->getDest()->getInfo() << " - Weight: "
                 << b->getWeight() << endl;
        }
    }
}
