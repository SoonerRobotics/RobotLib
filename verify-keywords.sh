# Make temporary folder to hold "correct" keywords
mkdir keywords

# Build keywords into that folder, ignore output
~/.local/bin/arduino-keywords src --output ../keywords

# Remove operator= from keywords.txt
sed -i '/operator=/d' keywords/keywords.txt

# Verify that keywords are correct
if ! cmp --silent keywords.txt keywords/keywords.txt; then
    echo "keywords.txt are not correct. Please run build.sh to generate keywords.txt!"
    exit 1
fi