import os
import re
import sys
import PyPDF2

def extract_turn_in_info(pdf_path):
    turn_in_info = []
    chapter_prefix = None
    
    with open(pdf_path, 'rb') as file:
        reader = PyPDF2.PdfReader(file)
        num_pages = len(reader.pages)
        
        for page_num in range(num_pages):
            page = reader.pages[page_num]
            text = page.extract_text()
            
            # Extract the chapter prefix (e.g., "C04")
            if not chapter_prefix:
                chapter_match = re.search(r'C Piscine\s+(C\s+\d+)', text)
                if chapter_match:
                    chapter_prefix = chapter_match.group(1).replace(" ", "")

            if "Turn-in directory" in text and "Files to turn in" in text:
                turn_in_dirs = re.findall(r'Turn-in directory\s*:\s*(\S+)', text)
                files_to_turn_in = re.findall(r'Files to turn in\s*:\s*(\S+)', text)
                if turn_in_dirs and files_to_turn_in:
                    turn_in_info.append((turn_in_dirs[0], files_to_turn_in[0]))
    
    return chapter_prefix, turn_in_info

def create_directories_and_files(chapter_prefix, turn_in_info):
    if not chapter_prefix:
        print("Chapter prefix not found.")
        return
    
    for turn_in_dir, file_to_turn_in in turn_in_info:
        full_dir_path = os.path.join(chapter_prefix, turn_in_dir)
        if not os.path.exists(full_dir_path):
            os.makedirs(full_dir_path)
        open(os.path.join(full_dir_path, file_to_turn_in), 'w').close()

def main():
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} <pdf_file_path>")
        sys.exit(1)
    
    pdf_path = sys.argv[1]
    chapter_prefix, turn_in_info = extract_turn_in_info(pdf_path)
    
    if not chapter_prefix:
        print("Error: Chapter prefix not found.")
        sys.exit(1)
    
    create_directories_and_files(chapter_prefix, turn_in_info)
    print(f"Directories and files created successfully under {chapter_prefix}.")

if __name__ == "__main__":
    main()

