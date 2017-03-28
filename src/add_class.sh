#!/bin/bash

CLASS_NAME=$1
GUARD_NAME="SLIM_HTTP_$(echo ${CLASS_NAME} | awk '{print toupper($0)}')"

rm ${CLASS_NAME}.{h,c}pp
touch ${CLASS_NAME}.{h,c}pp

echo "#ifndef ${GUARD_NAME}_HPP" >> ${CLASS_NAME}.hpp
echo "#define ${GUARD_NAME}_HPP" >> ${CLASS_NAME}.hpp
echo "" >> ${CLASS_NAME}.hpp
echo "namespace slim_http" >> ${CLASS_NAME}.hpp
echo "{" >> ${CLASS_NAME}.hpp
echo "" >> ${CLASS_NAME}.hpp
echo "class ${CLASS_NAME}" >> ${CLASS_NAME}.hpp
echo "{" >> ${CLASS_NAME}.hpp
echo "};" >> ${CLASS_NAME}.hpp
echo "" >> ${CLASS_NAME}.hpp
echo "}" >> ${CLASS_NAME}.hpp
echo "#endif // ${GUARD_NAME}_HPP" >> ${CLASS_NAME}.hpp

echo "#include \"${CLASS_NAME}.hpp\"" >> ${CLASS_NAME}.cpp
echo "" >> ${CLASS_NAME}.cpp
echo "namespace slim_http" >> ${CLASS_NAME}.cpp
echo "{" >> ${CLASS_NAME}.cpp
echo "}" >> ${CLASS_NAME}.cpp
