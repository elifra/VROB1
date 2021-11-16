FILE(REMOVE_RECURSE
  "core*"
  "*~"
  "gmon.out"
  "DartTestfile.txt"
  "CMakeFiles/tp6.dir/tp6.cpp.o"
  "tp6.pdb"
  "tp6"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang CXX)
  INCLUDE(CMakeFiles/tp6.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
