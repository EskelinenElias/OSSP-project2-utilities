echo "Running tests for wcat"
cd wcat
./test-wcat.sh

echo "Running tests for wgrep"
cd ../wgrep
./test-wgrep.sh

echo "Running tests for wzip"
cd ../wzip
./test-wzip.sh

echo "Running tests for wunzip"
cd ../wunzip
./test-wunzip.sh
