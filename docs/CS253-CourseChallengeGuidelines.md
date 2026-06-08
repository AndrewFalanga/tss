**CS 253: Software Development in C**

**Course Challenge Portfolio Guidelines**

# **Overview**

Students who believe they have already mastered the material covered in CS 253: Software Development in C may petition to challenge the course by submitting a portfolio of prior work accompanied by a reflective essay. This document outlines the requirements and procedures for the course challenge process.

The purpose of the course challenge is to allow students to demonstrate, through existing work and written analysis, that they have already achieved the learning objectives of the course. This is not a test or exam; rather, it is an opportunity to present evidence of competency gained through prior experience, coursework, or self-directed study.

# **Submission Requirements**

A complete course challenge submission consists of two components: a portfolio of work and a reflective essay. Both components must be submitted together for the challenge to be considered.

## **Component 1: Portfolio of Work**

The portfolio must consist of one or more GitHub repositories containing C programs and related artifacts that demonstrate mastery of the course learning objectives. Students should submit links to these repositories as part of their submission.

**Repository Access Requirements:**

* **Public repositories:** Simply provide the URL to the repository.

* **Private repositories:** Add the GitHub user **lhindman** as a collaborator so that the instructor can review the work. Navigate to your repository’s *Settings → Collaborators → Add people* and enter the username **lhindman**.

**Portfolio Expectations:**

* All submitted code must compile without warnings or errors using gcc with appropriate warning flags (e.g., \-Wall \-Wextra \-Wpointer-arith \-Wstrict-prototypes).

* Programs should run without memory errors as verified by valgrind.

* Repositories should include a Makefile that builds the project.

* Code should follow a consistent style guide and demonstrate secure coding practices.

* Commit history should demonstrate meaningful use of revision control (not a single bulk commit).

## **Component 2: Reflective Essay**

The reflective essay is the critical component of the challenge submission. In this essay, the student must clearly and specifically demonstrate how their portfolio work satisfies each of the Terminal Learning Objectives (TLOs) and their Supporting Learning Objectives (SLOs) listed in Section 3 of this document.

**Essay Requirements:**

* The essay must address ***every*** Terminal Learning Objective and its associated Supporting Learning Objectives.

* For each objective, the student must provide specific references to files, functions, code sections, or other artifacts within their portfolio repositories that demonstrate mastery of that objective.

* References should be precise. For example, rather than stating “my project uses structs,” the student should identify the specific file, line numbers, and explain how the code demonstrates competency (e.g., “In myproject/src/student.c, lines 45–78, I define a Student struct and access its members using both the dot operator and the dereference operator via a pointer, demonstrating SLO 1.2.”).

* For objectives that require explanation or description (e.g., 2.3, 3.1, 4.3), the essay must include a written explanation that demonstrates understanding of the concept, in addition to any code references where applicable.

* The essay should be well-organized, clearly written, and use the TLO/SLO numbering system to structure the discussion.

# **Course Learning Objectives**

The following tables list the Terminal Learning Objectives (TLOs) and their associated Supporting Learning Objectives (SLOs) for CS 253\. The reflective essay must address every objective listed below.

| TLO 1 | Develop a program using the C programming language that implements specific requirements without warnings, errors or memory issues. |
| :---- | :---- |
| 1.1 | Demonstrate arrays in C using both pointer and index based notation. |
| 1.2 | Demonstrate structs in C using both the dot (.) and dereference (-\>) operators. |
| 1.3 | Demonstrate functions in C by implementing the required functions as specified in a provided header file. |
| 1.4 | Demonstrate usage of pointers with arrays, structs and functions. |
| 1.5 | Demonstrate usage of input/output streams as well as file based I/O. |
| 1.6 | Demonstrate general C programming skills using library functions, variables, loops and/or conditionals. |

| TLO 2 | Develop a program that effectively uses the four memory segments that make up the C Memory Layout (text, data, heap and stack). |
| :---- | :---- |
| 2.1 | Identify where variables are allocated within the C Memory Layout (text, data, heap, stack). |
| 2.2 | Demonstrate dynamic memory allocation using the Create/Destroy design pattern. |
| 2.3 | Explain how variables in a given memory segment are declared and initialized as well as identify any limitations of this memory segment. |

| TLO 3 | Use industry standard tools to develop C programs. |
| :---- | :---- |
| 3.1 | Describe what occurs at each step of the build process (preprocessing, compiling, assembling, linking) as well as any artifacts that are generated. |
| 3.2 | Identify specific features of the make build automation tool that enable it to improve the development process. |
| 3.3 | Use revision control tool to clone, commit and push code from/to a remote repository. |
| 3.4 | Use integrated development environment (IDE) to develop C programs. |

| TLO 4 | Test, analyze and resolve issues (bugs) in C programs. |
| :---- | :---- |
| 4.1 | Identify the specific type of error (compile time, run time, logic, memory) as well as the appropriate debugging procedure to begin diagnosing it. |
| 4.2 | Use debugging tool to view the contents of variables, dereference dynamically allocated memory to view its contents, step into / over functions and set conditional breakpoints while processing large datasets. |
| 4.3 | Describe integration and unit testing, explaining why both are critical when developing robust C programs. |
| 4.4 | Test C programs using a provided test plan to perform both integration and unit tests. |

| TLO 5 | Apply secure programming practices related to code readability, the build process, error handling, input validation and memory access as specified in the SEI CERT C Coding Standard. |
| :---- | :---- |
| 5.1 | Describe secure programming issues related to code readability, the build process, error handling, input validation and memory access as specified in the SEI CERT C Coding Standard. |
| 5.2 | Use a style guide to write code that adheres to secure coding practices and that improves code readability. |
| 5.3 | Use warning features of the gcc compiler to identify and resolve common secure programming issues at compile time. |
| 5.4 | Devise error handling strategies using loops, conditionals and/or return values to appropriately handle error conditions when calling functions. |
| 5.5 | Devise error handling strategies using loops and/or conditionals to appropriately handle unexpected user input. |
| 5.6 | Demonstrate the valgrind memory analysis tool and explain the types of memory errors it can help diagnose. |

| TLO 6 | Understand how standard Linux/Unix system tools interact with the underlying system API and can be combined using the Stream Processing design pattern. |
| :---- | :---- |
| 6.1 | Explain how the standard Linux/Unix system tools (ls, cat, wc, grep, find, ps) function and be able to identify some of the underlying system API calls they use. |
| 6.2 | Demonstrate understanding of system API calls by implementing simplified versions of the standard Linux/Unix system tools (ls, cat, wc, grep, find, ps). |
| 6.3 | Explain how the stream processing design pattern and PIPEs can be used to solve problems using the standard Linux/Unix system tools. |

# **Evaluation Criteria**

The course challenge submission will be evaluated based on the following criteria:

1. **Completeness:** Does the submission address every TLO and SLO?

2. **Code Quality:** Does the portfolio code compile cleanly, run without memory errors, and follow secure coding practices?

3. **Specificity of Evidence:** Does the essay provide specific, precise references to portfolio artifacts for each objective?

4. **Depth of Understanding:** Does the essay demonstrate genuine understanding of concepts, particularly for objectives that require explanation?

5. **Use of Tools:** Does the portfolio demonstrate effective use of the required development tools (gcc, make, git, valgrind, a debugger, an IDE)?

A submission that fails to address one or more TLOs, or that provides only vague or superficial references to portfolio work, will not be approved. Students whose submissions are not approved are welcome to enroll in the course.

# **Submission Process**

6. Prepare your GitHub repositories and ensure they are accessible (public or with collaborator access granted to **lhindman**).

7. Write your reflective essay addressing all TLOs and SLOs with specific references to your portfolio work.

8. Submit both the list of repository links and the essay to the instructor via email.

9. Allow adequate time for review. The instructor will evaluate the submission and notify the student of the outcome.

**Questions?** If you have questions about the course challenge process or need clarification on any of the learning objectives, please contact the instructor before beginning your submission.