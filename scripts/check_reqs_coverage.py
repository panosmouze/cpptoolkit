#!/usr/bin/env python3
import os
import re

REQUIREMENTS_FILE = "docs/requirements.md"
TEST_DIR = "tests/"
INCLUDE_DIR = "include/"
IGNORE_FILE = "docs/reqs.ignore"

REQ_PATTERN = re.compile(r"\b(FR-\d{3}-\d{3}-\d{3})\b")

def extract_requirements(file_path):
    """Extracts requirement IDs from the requirements.md file."""
    with open(file_path, "r", encoding="utf-8") as file:
        content = file.read()
    return set(REQ_PATTERN.findall(content))

def search_for_requirements_in_files(directory, extensions):
    """Searches for requirement IDs in given file types within a directory."""
    found_reqs = set()
    
    for root, _, files in os.walk(directory):
        for file in files:
            if file.endswith(extensions):
                with open(os.path.join(root, file), "r", encoding="utf-8", errors="ignore") as f:
                    content = f.read()
                    found_reqs.update(REQ_PATTERN.findall(content))
    
    return found_reqs

def main():
    all_requirements = extract_requirements(REQUIREMENTS_FILE)
    ignored_requirements = extract_requirements(IGNORE_FILE)

    print(f"Total requirements found: {len(all_requirements)}")
    print(f"Ignored requirements: {len(ignored_requirements)}")

    tested_reqs = search_for_requirements_in_files(TEST_DIR, (".cpp",))
    implemented_reqs = search_for_requirements_in_files(INCLUDE_DIR, (".hpp",))

    untested_reqs = (all_requirements - tested_reqs) - ignored_requirements
    unimplemented_reqs = all_requirements - implemented_reqs

    print("\n===== REQUIREMENT CHECK REPORT =====")

    if not untested_reqs:
        print("All requirements are tested or ignored.")
    else:
        print("The following requirements are NOT tested:\n")
        print(sorted(untested_reqs))

    if not unimplemented_reqs:
        print("All requirements are linked in header files.")
    else:
        print("The following requirements are NOT implemented:\n")
        print(sorted(unimplemented_reqs))
    
    print("\n===== REQUIREMENT COVERAGE REPORT =====")

    print("The percentage of implemented & linked reqs: ", int((len(implemented_reqs)/len(all_requirements))*100), "%")
    print("The percentage of tested reqs: ", int((len(tested_reqs)/len(all_requirements))*100), "%")

    if untested_reqs or unimplemented_reqs:
        exit(1)
    else:
        exit(0)

if __name__ == "__main__":
    main()
