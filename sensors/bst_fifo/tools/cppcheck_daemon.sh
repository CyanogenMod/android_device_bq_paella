if [ "$1" == "" ] ;  then
echo "usage: $0 daemon_path"
exit 1
fi

DIR_SCRIPT=$PWD/$(dirname $0)

cd $1

cppcheck -v --force --error-exitcode=255 --enable=all --inconclusive --std=posix --suppress=variableScope  --suppress=functionStatic --quiet --suppress=redundantAssignment --suppress=variableScope --suppress=cstyleCast --suppress=redundantCopy --suppress=ConfigurationNotChecked --suppress=unusedFunction --suppress=obsoleteFunctionsusleep --suppress=missingInclude --template='{file}:{line},{severity},[{id}],{message}' .


ret=$?
if [ $ret != 0 ]; then
    echo "cppcheck detected errors: $ret"
    exit $ret
fi

echo "$1 passed static analysis by cppcheck!"
