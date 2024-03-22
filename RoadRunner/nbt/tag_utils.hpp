#pragma once

#include <nbt/tag/tag.hpp>

using RoadRunner::nbt::tag::Tag;

Tag *create_tag(TagIdentifiers id);
void print_tag(Tag* id);