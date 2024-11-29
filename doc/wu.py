import os
import re

def parse_wu_file(wu_file):
    """Parse a .wu file to extract relevant documentation sections."""
    doc_data = {
        'name': '',
        'synopsis': '',
        'parameters': [],
        'description': '',
        'seealso': []
    }
    
    with open(wu_file, 'r') as f:
        content = f.read()
        
        # Extract Title (Name)
        match = re.search(r"^Title:\s*(\S+)", content, re.M)
        if match:
            doc_data['name'] = match.group(1)
        
        # Extract SYNOPSIS
        match = re.search(r"^SYNOPSIS\n=+\n(.*?)(?=\n\n|$)", content, re.S)
        if match:
            doc_data['synopsis'] = match.group(1).strip()

        # Extract PARAMETERS
        match = re.search(r"^PARAMETERS\n=+\n(.*?)(?=\n\n|$)", content, re.S)
        if match:
            param_section = match.group(1).strip().split('\n')
            for param in param_section:
                doc_data['parameters'].append(param.strip().replace('* #', ''))

        # Extract DESCRIPTION
        match = re.search(r"^DESCRIPTION\n=+\n(.*?)(?=\n\n|$)", content, re.S)
        if match:
            doc_data['description'] = match.group(1).strip()

        # Extract SEE ALSO
        match = re.search(r"^SEE ALSO\n=+\n(.*?)(?=\n\n|$)", content, re.S)
        if match:
            see_also_section = match.group(1).strip().split(',')
            doc_data['seealso'] = [item.strip() for item in see_also_section]
    
    return doc_data


def generate_doxygen_comment(func_name, doc_data):
    """Generate a Doxygen-style comment block from parsed data."""
    doxygen_comment = f"/**\n * @{func_name}\n *\n"
    doxygen_comment += f" * @brief {doc_data['description']}\n *\n"
    
    doxygen_comment += f" * ## SYNOPSIS:\n * ```\n * {doc_data['synopsis']}\n * ```\n *\n"
    
    if doc_data['parameters']:
        doxygen_comment += " * ## PARAMETERS:\n"
        for param in doc_data['parameters']:
            doxygen_comment += f" * @param {param}\n"
    
    if doc_data['seealso']:
        doxygen_comment += " * ## SEE ALSO:\n"
        for item in doc_data['seealso']:
            doxygen_comment += f" * @{item}\n"
    
    doxygen_comment += " */\n"
    
    return doxygen_comment


def update_header_file(header_file, wu_file):
    """Update a header file by merging .wu documentation into Doxygen comments."""
    doc_data = parse_wu_file(wu_file)
    
    # Read the original header file
    with open(header_file, 'r') as f:
        header_content = f.read()
    
    # Extract function name (assuming the function is declared on the same line as the comment)
    match = re.search(r"\bvoid\s+(\w+)\s*\(", header_content)
    if match:
        func_name = match.group(1)
        
        # Generate Doxygen comment
        doxygen_comment = generate_doxygen_comment(func_name, doc_data)
        
        # Replace the old comment block with the Doxygen comment
        updated_content = re.sub(r"/\*.*?\*/", doxygen_comment, header_content, flags=re.S)
        
        # Write back the updated content to the header file
        with open(header_file, 'w') as f:
            f.write(updated_content)


def process_directory(header_dir, wu_dir):
    """Process all header files in a directory."""
    for filename in os.listdir(wu_dir):
        if filename.endswith('.wu'):
            wu_file = os.path.join(wu_dir, filename)
            header_file = os.path.join(header_dir, filename.replace('.wu', '.h'))
            
            if os.path.exists(wu_file):
                update_header_file(header_file, wu_file)
                print(f"Updated {header_file}")
                continue
                
            header_file = os.path.join(header_dir, filename.replace('.wu', '.h'))
                
            else:
                print(f"Missing .wu file for {header_file}")


# Example usage
root_directory = '/home/domson/Development/starbase'
header_directory = root_directory + '/tablelib'
wu_directory = root_directory + '/doc'
process_directory(header_directory, wu_directory)
