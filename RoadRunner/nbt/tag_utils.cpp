#include <nbt/tag_utils.hpp>
#include <nbt/tag/byte.hpp>
#include <nbt/tag/short.hpp>
#include <nbt/tag/int.hpp>
#include <nbt/tag/long.hpp>
#include <nbt/tag/float.hpp>
#include <nbt/tag/double.hpp>
#include <nbt/tag/byte_array.hpp>
#include <nbt/tag/string.hpp>
#include <nbt/tag/list.hpp>
#include <nbt/tag/compound.hpp>
#include <nbt/tag/int_array.hpp>
#include <nbt/tag/long_array.hpp>

using RoadRunner::nbt::tag::Byte;
using RoadRunner::nbt::tag::Short;
using RoadRunner::nbt::tag::Int;
using RoadRunner::nbt::tag::Long;
using RoadRunner::nbt::tag::Float;
using RoadRunner::nbt::tag::Double;
using RoadRunner::nbt::tag::ByteArray;
using RoadRunner::nbt::tag::String;
using RoadRunner::nbt::tag::List;
using RoadRunner::nbt::tag::Compound;
using RoadRunner::nbt::tag::IntArray;
using RoadRunner::nbt::tag::LongArray;
static int tabcnt = 0;
void print_tag(Tag* tag){

       union{
            ByteArray* bar;
            List* list;
            Compound* comp;
            IntArray* iar;
            LongArray* lar;
       } tag2;
    printf("%s", std::string(tabcnt, '\t').c_str());
    switch (tag->id) {
        
        case TagIdentifiers::BYTE:
            printf("TAG_BYTE(%s)=%d\n", tag->name.c_str(), ((Byte*)tag)->value);
            break;
        case TagIdentifiers::SHORT:
            printf("TAG_SHORT(%s)=%d\n", tag->name.c_str(), ((Short*)tag)->value);
            break;
        case TagIdentifiers::INT:
            printf("TAG_INT(%s)=%d\n", tag->name.c_str(), ((Int*)tag)->value);
            break;
        case TagIdentifiers::LONG:
            printf("TAG_LONG(%s)=%lld\n", tag->name.c_str(), ((Long*)tag)->value);
            break;
        case TagIdentifiers::FLOAT:
            printf("TAG_FLOAT(%s)=%f\n", tag->name.c_str(), ((Float*)tag)->value);
            break;
        case TagIdentifiers::DOUBLE:
            printf("TAG_DOUBLE(%s)=%f\n", tag->name.c_str(), ((Double*)tag)->value);
            break;
        case TagIdentifiers::BYTE_ARRAY:
            tag2.bar = ((ByteArray*)tag);
            printf("TAG_BYTEARRAY(%s)={\n", tag->name.c_str());

            ++tabcnt;

            for(int i = 0; i < tag2.bar->size; ++i){
                 printf("%s", std::string(tabcnt, '\t').c_str());
                 printf("%d, ", tag2.bar->value[i]);
            }

            --tabcnt;

            printf("}\n");
            break;
        case TagIdentifiers::STRING:
            printf("TAG_STRING(%s)=%s\n", tag->name.c_str(), ((String*)tag)->value.c_str());
            break;
        case TagIdentifiers::LIST:
            tag2.list = (List*) tag;
            printf("TAG_LIST(%s)={\n", tag->name.c_str());

            ++tabcnt;

            for(int i = 0; i < tag2.list->size; ++i){
                print_tag(tag2.list->value[i]);
            }

            --tabcnt;
            printf("%s", std::string(tabcnt, '\t').c_str());
            printf("}\n");
            break;
        case TagIdentifiers::COMPOUND:
            tag2.comp = (Compound*) tag;
            printf("TAG_COMPOUND(%s)={\n", tag->name.c_str());

            ++tabcnt;

            for(auto tg : tag2.comp->value){
                print_tag(tg);
            }

            --tabcnt;
            printf("%s", std::string(tabcnt, '\t').c_str());
            printf("}\n");
            break;
        case TagIdentifiers::INT_ARRAY:
            tag2.iar = ((IntArray*)tag);
            printf("TAG_INTARRAY(%s)={\n", tag->name.c_str());

            ++tabcnt;

            for(int i = 0; i < tag2.iar->size; ++i){
                 printf("%s", std::string(tabcnt, '\t').c_str());
                 printf("%d, ", tag2.iar->value[i]);
            }

            --tabcnt;
            printf("%s", std::string(tabcnt, '\t').c_str());
            printf("}\n");
            break;
        case TagIdentifiers::LONG_ARRAY:
            tag2.lar = ((LongArray*)tag);
            printf("TAG_LONGARRAY(%s)={\n", tag->name.c_str());

            ++tabcnt;

            for(int i = 0; i < tag2.lar->size; ++i){
                 printf("%s", std::string(tabcnt, '\t').c_str());
                 printf("%lld, ", tag2.lar->value[i]);
            }

            --tabcnt;
            printf("%s", std::string(tabcnt, '\t').c_str());
            printf("}\n");
            break;
        default:
            break;
    }
}
Tag *create_tag(TagIdentifiers id) {
    switch (id) {
    case TagIdentifiers::BYTE:
        return new Byte();
    case TagIdentifiers::SHORT:
        return new Short();
    case TagIdentifiers::INT:
        return new Int();
    case TagIdentifiers::LONG:
        return new Long();
    case TagIdentifiers::FLOAT:
        return new Float();
    case TagIdentifiers::DOUBLE:
        return new Double();
    case TagIdentifiers::BYTE_ARRAY:
        return new ByteArray();
    case TagIdentifiers::STRING:
        return new String();
    case TagIdentifiers::LIST:
        return new List();
    case TagIdentifiers::COMPOUND:
        return new Compound();
    case TagIdentifiers::INT_ARRAY:
        return new IntArray();
    case TagIdentifiers::LONG_ARRAY:
        return new LongArray();
    default:
        return nullptr;
    }
}