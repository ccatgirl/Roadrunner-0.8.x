#include <config.hpp>
#include <server.hpp>
#include <nbt/tag_utils.hpp>
#include <nbt/tag/compound.hpp>

#include <nbt/tag_identifiers.hpp>
using RoadRunner::Server;

int main(int argc, char** argv) {
    Server *server = new Server(19132, MAX_CLIENTS);
}
