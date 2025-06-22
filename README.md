# JQen

JQen is a template rendering engine for JavaScript, powered by the [Qentem Engine](https://github.com/HaniAmmar/Qentem-Engine) and delivered as WebAssembly.&#x20;
It enables fast, safe, and efficient template rendering with JSON data directly in web browsers.

---

## Table of Contents

-   [What is JQen?](#what-is-jqen)
-   [Features](#features)
-   [Usage](#usage)
    -   [Live Testing](#live-testing)
    -   [Variable](#variable)
    -   [Math](#math)
    -   [Inline If](#inline-if)
    -   [Loop](#loop)
    -   [If Condition](#if-condition)
-   [Page Example](#page-example)
-   [Reference](#reference)
-   [Build WASM](#build-wasm)
-   [License](#license)

---

## What is JQen?

JQen is a JavaScript module that leverages the Qentem Engine library (via WebAssembly) for fast, safe, and expressive template rendering.
Bring the full power of C++ template parsing and JSON data handling to web browsers.

---

## Features

-   Fast template rendering implemented in C++ and compiled to WebAssembly.
-   Low memory overhead.
-   Safe evaluation without arbitrary code execution.
-   Variable replacement with automatic HTML escaping.
-   Raw variable replacement (without HTML escaping) is also supported.
-   Nested loops with grouping and sorting.
-   Nested if conditions and inline conditional tags.
-   Arithmetic evaluation via the math tag.

---

## Usage

### Live Testing

JQen templates can be tested live at [JQen Tool](https://haniammar.github.io/JQen-Tool).

---

### Variable

Insert variables into your template using `{var:...}` syntax:

```js
var Module,
    data,
    template = `
<div>{var:v1}</div>
<div>{var:sub-list1[sv1]}</div>
<div>{var:sub-list2[0]}</div>
`;

data = '{"v1":"Qentem","sub-list1":{"sv1":"JQen"},"sub-list2":[77]}';

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(
            template,
            data,
            "template name" // Optional: name for parsed template cache.
        );
    },
};
```

---

### Math

Evaluate arithmetic expressions in your template:

```js
var Module,
    data,
    template = `
<div>0.1+0.2 is: {math: 0.1 + 0.2}</div>
<div>{var:one}+{var:four}*{var:two}+{var:one} = {math:{var:one}+{var:four}*{var:two}+{var:one}}</div>
<div>6^2 = {math:6^2}</div>
<div>{var:one}+{var:three} = {math:{var:one}+{var:three}}</div>
<div>9 % 5 = {math:9 % 5}</div>
`;

data = '{"one":1,"two":2,"three":3,"four":4}';

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(template, data, "template name");
    },
};
```

---

### Inline If

Add conditional logic directly within templates:

```js
var Module,
    data,
    template = `
<div>{if case="{var:one} + {var:two} >= {var:three}" true="3" false="not three"}</div>
<div>{if case="{var:one}" true="{var:one}" false="not one"}</div>
{if case="{var:name} == Qentem" true="<div>Qentem!</div>"}
`;

data = '{"one":"1","two":"2","three":"3","name":"Qentem"}';

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(template, data, "template name");
    },
};
```

---

### Loop

Render arrays and objects using loops:

```js
var Module,
    data,
    template = `
<loop set="object" value="item">
    <div>{var:item[var1]} {var:item[var2]} {var:item[var3]} {var:item[var4]}</div>
</loop>
<br />
<loop set="array" value="item">
    <div>{var:item[0]} {var:item[1]} {var:item[2]} {var:item[3]}</div>
</loop>
`;

data = `
{
    "object": [
        {"var1": "value1", "var2": "value2", "var3": "value3", "var4": "value4"},
        {"var1": "value5", "var2": "value6", "var3": "value7", "var4": "value8"}
    ],
    "array": [
        ["value10", "value20", "value30", "value40"],
        ["value100", "value200", "value300", "value400"]
    ]
}`;

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(template, data, "template name");
    },
};
```

---

### If Condition

Use full conditional blocks for complex logic:

```js
var Module,
    data,
    template = `
<if case="{var:0} == 0">
<div>Zero!</div>
</if>

<if case="{var:1} == 0">
Zero!
<else />
<div>Not {var:0} but {var:1}.</div>
</if>

<if case="{var:2} == 0">
Zero!
<else if case="{var:2} == 2">
<div>Two!</div>
<else />
Not zero or one.
</if>

<if case="{var:2} == 0">
Zero!
<else if case="{var:2} == 5">
Two!
<else if case="{var:3} == 3">
<div>{var:3}</div>
<else>
Not zero or one or two.
</if>`;

data = "[0,1,2,3]";

Module = {
    onRuntimeInitialized: function () {
        JQen_Render(
            template,
            data,
            "template name" // (Optional) Name to cache the parsed template.
        );
    },
};
```

---

## Page Example

A complete HTML page using JQen:

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <title>JQen Page Example</title>
    </head>
    <body>
        <div id="main"></div>
        <script>
            var Module,
                data,
                template = `<h2>Students' list:</h2>
<loop value="department_val">
    <h3>Major: {var:department_val[major]}</h3>
    <ul>
    <loop set="department_val[students]" value="student_val">
        <li>
            <span>Name: {var:student_val[Name]}</span>
            <span>
                GPA: {var:student_val[GPA]}
                <if case="{var:student_val[GPA]} < 2.5"> (Inform adviser!)
                <else if case="{var:student_val[GPA]} >= 3.5"> (President's List!)
                <else if case="{var:student_val[GPA]} >= 3.0"> (Dean's List!)
                </if>
            </span>
        </li>
    </loop>
    </ul>
</loop>`;

            data = [
                {
                    major: "Computer Science",
                    students: [
                        { Name: "Student1", GPA: 3.2 },
                        { Name: "Student2", GPA: 3.8 },
                        { Name: "Student3", GPA: 2.8 },
                    ],
                },
                {
                    major: "Math",
                    students: [
                        { Name: "Student4", GPA: 3.0 },
                        { Name: "Student5", GPA: 2.5 },
                        { Name: "Student6", GPA: 2.4 },
                    ],
                },
            ];

            Module = {
                onRuntimeInitialized: function () {
                    document.getElementById("main").innerHTML = Module.JQen_Render(
                        template,
                        JSON.stringify(data),
                        "MainPage"
                    );
                },
            };
        </script>
        <script src="JQen.js"></script>
    </body>
</html>
```

---

## Reference

Full template syntax: [Qentem-Engine/Template.md](https://github.com/HaniAmmar/Qentem-Engine/blob/main/Documentation/Template.md)

---

## Build WASM

1. **Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)**
2. **Build:**

```shell
git submodule update --init

mkdir Build
em++ -lembind -Oz -flto -fno-exceptions -std=c++17 -I ./qentem/Include ./Source/QLib.cpp -o ./Build/JQen.js
```

-   Compiled WASM files and releases:
    [JQen Releases](https://github.com/HaniAmmar/JQen/releases)

---

## License

See the [LICENSE](LICENSE) file for details.
