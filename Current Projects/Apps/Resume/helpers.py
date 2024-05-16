public_routes = [
    ('about', 'About Me'),
    ('projects', 'Projects'),
]

def file_content(file_name):
    with open(file_name, 'r') as file:
        content = file.read()
    # Replace newline characters with HTML line break
    content = content.replace('\n', '<br>')
    return content

def get_projects():
    project_summary = file_content('./txt/DDDQN_summary.txt')
        
    projects = [
        {
            'title': 'Double Dueling Deep Q-Network (DDDQN)',
            'description': project_summary,
            'image': None
        },
        {
            'title': 'Project 2',
            'description': 'This is a brief description of Project 2.',
            'image': None
        },
        {
            'title': 'Project 3',
            'description': 'This is a brief description of Project 3.',
            'image': None
        }
    ]
    
    return projects