#pragma once

#include <nbt/tag/tag.hpp>
#include <vector>

using RoadRunner::nbt::tag::Tag;

namespace RoadRunner {
    namespace nbt {
        namespace tag {
            class Compound : public Tag {
            public:
                std::vector<Tag *> value;
                bool unsafe = false;

                Compound();

                ~Compound();
                
                Tag* find(char* name){
                    for(Tag* tag : this->value){
                        if(tag->name._Equal(name)){
                            return tag;
                        }
                    }

                    return 0;
                }

                bool read(RakNet::BitStream *stream);

                void write(RakNet::BitStream *stream);
            };
        }
    }
}