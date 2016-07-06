#include <algorithm>
#include <cstdio>
#include <fstream>
#include <vector>
#include <string>


static bool compare(std::string a, std::string b);


struct Str
{
    char * str;
    int length;
};


struct Options
{
    Str prefix;
    Str header;
    Str load_procs;
    Str declarations;
    Str get_proc;
};


static Options options = {
    { "SB", 2 },
    { "include/gen/gl_header.inc", 13 },
    { "include/gen/gl_load_procs.inc", 16 },
    { "include/gen/gl_declarations.inc", 19 },
    { "GetProc", 7 }
};

static std::vector<std::string> functions;

static int max_length;


static void WriteHeaderFile()
{
    std::ofstream output;

    output.open(options.header.str);

    for (auto const &func : functions)
    {
        std::string upper;

        // NOTE (Emil): Temp buffer for holding the formatted string.
        char buffer[200] = {};

        // NOTE (Emil): Uppercase the function name.
        for (auto c: func)
        {
            upper.push_back(toupper(c));
        }

        sprintf(
            buffer,
            "extern PFN%sPROC%-*s%s%s;\n",
            upper.c_str(),
            (int)(max_length + 1 - func.length()),
            " ",
            options.prefix.str,
            func.c_str()
        );

        auto result = strstr(buffer, "\n");
        *(result + 1) = '\0';

        output.write(buffer, result + 1 - buffer);
    }

    output.write("\n\n", 2);

    for (auto const &func : functions)
    {
        char buffer[200] = {};

        sprintf(
            buffer,
            "#define %s%-*s%s%s\n",
            func.c_str(),
            (int)(max_length + 1 - func.length()),
            " ",
            options.prefix.str,
            func.c_str()
        );

        auto result = strstr(buffer, "\n");
        *(result + 1) = '\0';

        output.write(buffer, result + 1 - buffer);
    }

    output.close();
}



static void WriteGetProceduresFile ()
{
    std::ofstream output;

    output.open(options.load_procs.str);

    for (auto const &func : functions)
    {
        char buffer[200] = {};
        std::string upper;

        // NOTE (Emil): Uppercase the function name.
        for (auto c: func)
        {
            upper.push_back(toupper(c));
        }

        sprintf(
            buffer,
            "%s%-*s= (PFN%sPROC)%s(\"%s\");\n",
            func.c_str(),
            (int)(max_length + 1 - func.length()),
            " ",
            upper.c_str(),
            options.get_proc.str,
            func.c_str()
        );

        auto result = strstr(buffer, "\n");
        *(result + 1) = '\0';

        output.write(buffer, result + 1 - buffer);
    }

    output.close();
}


static void WriteDeclarationsFile ()
{
    std::ofstream output;

    output.open(options.declarations.str);

    for (auto const &func : functions)
    {
        char buffer[200] = {};
        std::string upper;

        // NOTE (Emil): Uppercase the function name.
        for (auto c: func)
        {
            upper.push_back(toupper(c));
        }

        sprintf(
            buffer,
            "PFN%sPROC%-*s%s;\n",
            upper.c_str(),
            (int)(max_length + 1 - func.length()),
            " ",
            func.c_str()
        );

        auto result = strstr(buffer, "\n");
        *(result + 1) = '\0';

        output.write(buffer, result + 1 - buffer);
    }

    output.close();
}


int main (int argc, char ** argv)
{
    if (argc < 2)
    {
        printf("Usage: \n\nglGenerate input_filename [output_dir]\n");

        return 0;
    }

    const char * filename = argv[1];

    std::ifstream input;


    input.open(filename);

    std::string line;

    while (std::getline(input, line))
    {
        if (line.length() > 0)
        {
            functions.push_back(line);
        }
    }

    input.close();

    auto max = std::max_element(functions.begin(), functions.end(), compare);
    max_length = (int)(*max).length();

    WriteHeaderFile();
    WriteGetProceduresFile();
    WriteDeclarationsFile();
}

static bool compare (std::string a, std::string b)
{
    return (a.length() < b.length());
}
