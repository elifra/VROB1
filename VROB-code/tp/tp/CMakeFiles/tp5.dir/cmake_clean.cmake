FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp5.dir/tp5.cpp.o"
  "tp5.pdb"
  "tp5"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp5.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
