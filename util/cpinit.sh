#!/bin/bash

# Check if CP_UTILS environment variable is set
if [ -z "$CP_UTILS" ]; then
  echo "Error: CP_UTILS environment variable is not set."
  exit 1
fi

# Define the source template directory
template_dir="$CP_UTILS/template"

# Check if the template directory exists
if [ ! -d "$template_dir" ]; then
  echo "Error: Template directory '$template_dir' does not exist."
  exit 1
fi

# Create 5 copies of the template directory
for i in {1..5}; do
  target_dir="task$i"
  cp -r "$template_dir" "$target_dir"
  if [ $? -ne 0 ]; then
    echo "Error: Failed to copy template to $target_dir"
    exit 1
  fi
done

exit 0
