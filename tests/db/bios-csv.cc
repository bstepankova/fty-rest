#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "db/inout.h"
#include "log.h"
#include "csv.h"

static void
s_usage()
{
    std::cerr << "Usage: bios-cli [export|compare]" << std::endl;
    std::cerr << "       export     export csv file from current DB" << std::endl;
    std::cerr << "       compare    sourcefile_1 exportedfile_2  return exportedfile_2 corresponds with sourcefile_1" << std::endl;
}

static void
s_die_usage()
{
    s_usage();
    exit(EXIT_FAILURE);
}

static bool
s_compare(
        const char* file1,
        const char* file2)
{
    std::ifstream   sfile1{file1};
    std::ifstream   sfile2{file2};

    shared::CsvMap c1 = shared::CsvMap_from_istream(sfile1);
    shared::CsvMap c2 = shared::CsvMap_from_istream(sfile2);

    // 1. number of rows must be the same
    if (c1.rows() != c2.rows()) {
        log_error("different number of rows, %s: %zu != %s: %zu", file1, c1.rows(), file2, c2.rows());
        return false;
    }

    auto t1 = c1.getTitles();
    auto t2 = c2.getTitles();

    // 2. for each line and each title, check the fields
    for (size_t line = 1; line != c1.rows(); line++) {
        auto unused_columns = t2;
        for (const std::string& title: t1) {
            if ( t2.count(title) == 0 )
            {
                // c1 has column named AAAA, but c2 doesn't
                if ( !c1.get(line, title).empty() ) {
                    log_error("%s[%zu][%s] = %s has no equivalent is %s",
                            file1, line, title.c_str(), c1.get(line, title).c_str(),
                            file2
                            );
                    return false;
                }
                else
                    unused_columns.erase(title);
            }
            else
            {
                // c1 has column named AAAA and c2 does
                if (c1.get(line, title) != c2.get(line, title)) {
                    log_error("%s[%zu][%s] = %s != %s[%zu][%s] = %s",
                            file1, line, title.c_str(), c1.get(line, title).c_str(),
                            file2, line, title.c_str(), c2.get(line, title).c_str()
                            );
                    return false;
                }
                else
                    unused_columns.erase(title);
            }
        }
        // c2 has more columns, than c1 -> the difference should be empty
        // but with one exception: "id"
        unused_columns.erase("id");
        for ( auto &one_col : unused_columns )
            if ( !c2.get(line, one_col).empty() )
            {
                log_error("%s[%zu][%s] = %s  has no equivalent in %s",
                        file2, line, one_col.c_str(), c2.get(line, one_col).c_str(),
                        file1
                        );
                return false;
            }
    }

    log_info("'%s' corresponds with '%s'", file2, file1);
    return true;
}

int main(int argc, char** argv)
{
    if (argc <= 1)
        s_die_usage();

    if (!strcmp(argv[1], "export"))
    {
        log_set_level(LOG_WARNING); //to suppress messages from src/db
        persist::export_asset_csv(std::cout);
    }
    else
    if (!strcmp(argv[1], "compare"))
    {
        log_set_level(LOG_INFO);
        if (argc < 4)
            s_die_usage();

        const char* file1 = argv[2];
        const char* file2 = argv[3];
        if (!s_compare(file1, file2))
            exit(EXIT_FAILURE);
    }
    else
    {
        log_error("Unknown command '%s'", argv[1]);
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);

}