
// Header File
#include "game/alg/los/processor.h"

// External Dependencies
#include <array>
#include <set>

// Internal Dependencies
#include "game/alg/los/octantprocessor.h"
#include "game/component/vision.h" // needed for relevant_octants() //TODO: find a way to remove

// Using
using std::set;

namespace game {
namespace alg {
namespace los {

Processor::Processor(component::Vision* vision) : vision_(vision) {
    for(int i=0; i<8; ++i)
        octants_[i] = new OctantProcessor(i,vision);
}

Processor::~Processor() {
    for(int i=0; i<8; ++i)
        delete octants_[i];
}

void Processor::Process() {
    set<int> relevant_octants = vision_->relevant_octants();

    for(auto rt = relevant_octants.begin(); rt != relevant_octants.end(); ++rt)
        octants_[*rt]->ProcessOctant();
}

} // namespace los
} // namespace alg
} // namespace game
