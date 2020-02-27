# Make temporary folder to hold "correct" keywords
mkdir keywords > /dev/null 2>&1

# Build keywords into that folder, ignore output
arduino-keywords src --output ../keywords > /dev/null 2>&1

# Remove operator= from keywords.txt
sed -i '/operator=/d' keywords/keywords.txt

# Verify that keywords are correct
if ! cmp --silent keywords.txt keywords/keywords.txt; then
    echo "keywords.txt are not correct. Please run build.sh to generate keywords.txt!"
    exit 1
fi