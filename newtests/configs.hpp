#ifndef __OSM2PGSQL_TESTS_MIDDLE_CONFIG_HPP
#define __OSM2PGSQL_TESTS_MIDDLE_CONFIG_HPP

#include "common-pg.hpp"

#include "options.hpp"

// The testfiles to use.
#define TEST_PBF "tests/liechtenstein-2013-08-03.osm.pbf"

// Various options settings to run the tests against.
namespace testing {
namespace options {

struct slim_default : options_t
{
    slim_default(pg::tempdb_t const &db)
    {
        database_options = db.db_options();
        prefix = "osm2pgsql_test";
        style = "default.style";
        slim = true;
        cache = 1;
        num_procs = 1;
    }
};

struct slim_dense_cache : slim_default
{
    slim_dense_cache(pg::tempdb_t const &db) : slim_default(db)
    {
        alloc_chunkwise = ALLOC_DENSE;
    }
};

struct gazetteer_default : options_t
{
    gazetteer_default(pg::tempdb_t const &db)
    {
        database_options = db.db_options();
        setup();
    }
    gazetteer_default() { setup(); }

    void setup()
    {
        output_backend = "gazetteer";
        style = "newtests/data/gazetteer-test.style";
    }

};

struct flat_nodes : options_t
{
    flat_nodes()
    {
        flat_node_file = boost::optional<std::string>(
            "newtests/test_middle_flat.flat.nodes.bin");
        flat_node_cache_enabled = true;
    }
};

struct slim_flat_nodes : slim_default
{
    slim_flat_nodes(pg::tempdb_t const &db)
    : slim_default(db)
    {
        flat_node_file = boost::optional<std::string>(
            "newtests/test_middle_flat.flat.nodes.bin");
        flat_node_cache_enabled = true;
    }
};

}
}

#endif // __OSM2PGSQL_TESTS_MIDDLE_CONFIG_HPP
