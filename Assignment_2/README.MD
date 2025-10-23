# XML Structure Validator

A C program that checks the structural validity of XML files by verifying proper tag nesting and matching.

## Overview

This program reads an XML file (`note.xml`) and validates its structure by ensuring:
- Every opening tag has a corresponding closing tag
- Tags are properly nested
- There are no mismatched tags
- No unclosed tags remain at the end of the file

## Features

- **Stack-based Validation**: Uses a stack to track opening tags
- **Comprehensive Tag Detection**: Handles various tag formats
- **Detailed Error Reporting**: Provides specific error messages for:
    - Mismatched opening and closing tags
    - Extra closing tags
    - Unclosed opening tags
- **Real-time Validation**: Processes the XML file line by line

## How It Works

### Algorithm
1. **Push Opening Tags**: When an opening tag (`<tag>`) is encountered, it's pushed onto the stack
2. **Pop on Closing Tags**: When a closing tag (`</tag>`) is found, the top of the stack is popped and compared
3. **Validation Check**:
    - If stack is empty when popping → Extra closing tag
    - If popped tag doesn't match closing tag → Mismatch
    - If stack not empty at end → Unclosed tags

### Supported Tag Types
- Regular opening tags: `<tag>`
- Closing tags: `</tag>`
- Self-closing tags: `<tag/>` (ignored)
- Ignores XML declarations (`<?...?>`) and comments (`<!...>`)

## Usage

### Compilation
```bash
gcc -o xml_validator xml_validator.c
```

### Running the Program
```bash
./xml_validator
```

### Requirements
- Input file must be named `note.xml` in the same directory
- File must be readable

## Output Examples

### Valid XML
```
Checking XML structure...
XML is valid!
```

### Invalid XML Scenarios

**Mismatched Tags:**
```
Checking XML structure...
Tag mismatch: expected </note> but found </message>
XML is invalid!
```

**Unclosed Tags:**
```
Checking XML structure...
Unclosed tags:
   - <note>
   - <body>
XML is invalid!
```

**Extra Closing Tags:**
```
Checking XML structure...
Extra closing tag found: </extra>
XML is invalid!
```

## Code Structure

### Global Variables
- `tagStack`: 2D array storing opening tags
- `top`: Stack pointer index

### Functions
- `pushTag(const char *tag)`: Adds tag to stack
- `popTag()`: Removes and returns top tag from stack
- `main()`: File processing and validation logic

### Constants
- `STACK_SIZE`: Maximum stack capacity (100 tags)
- `TAG_SIZE`: Maximum tag name length (50 characters)
- `LINE_SIZE`: Maximum line buffer size (256 characters)

## Limitations

- Does not validate XML attributes
- Does not check for proper XML declaration
- No support for CDATA sections
- Simple parsing may not handle all edge cases
- Fixed input filename (`note.xml`)

## Error Handling

- File opening failures
- Stack overflow protection
- Detailed error messages for structural issues
- Graceful handling of malformed tags

## Example Validation

**Valid XML:**
```xml
<note>
    <to>User</to>
    <from>Admin</from>
    <body>Message</body>
</note>
```

**Invalid XML (would be caught):**
```xml
<note>
    <to>User</to>
    <from>Admin</from>
    <body>Message</note>
</body>
```