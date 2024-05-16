public_routes = [
    ('about', 'About'),
]

def file_content(file_name):
    with open(file_name, 'r') as file:
        content = file.read()
    # Replace newline characters with HTML line break
    content = content.replace('\n', '<br>')
    return content

import sys
import os

print(os.path.dirname(sys.executable))