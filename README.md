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
const template = `
<div>{var:v1}</div>
<div>{var:sub-list1[sv1]}</div>
<div>{var:sub-list2[0]}</div>
`;

document.addEventListener("DOMContentLoaded", async () => {
    // This call initializes the WebAssembly module.
    // invoking LoadJQenRender() again would reinitialize the module,
    // which is inefficient and unnecessary. Instead, cache and reuse
    // the returned JQenRender() function for all rendering tasks.
    const JQenRender = await LoadJQenRender();

    // Call the renderer with the given template, data, and an optional name.
    // It returns the rendered HTML string, which we insert into the container element.
    // If a name is passed (e.g., "home_page"), the template will be cached and reused,
    // significantly improving performance — up to **3.5× faster** on repeated renders.
    document.getElementById("container").innerHTML = JQenRender(template, data, "Variables Example");
});
```

---

### Math

Evaluate arithmetic expressions in your template:

```js
const template = `
<div>0.1+0.2 is: {math: 0.1  +   0.2 }</div>
<div>{var:one}+{var:four}*{var:two}+{var:one} = {math:{var:one}+{var:four}*{var:two}+{var:one}}; (1+8+1)</div>
<div>6^2 = {math:6^2}</div>
<div>{var:one}+{var:three} = {math:{var:one}+{var:three}}</div>
<div>9 % 5 = {math:9 % 5}</div>
`;

const data = '{"one":1,"two":2,"three":3,"four":4}';

document.addEventListener("DOMContentLoaded", async () => {
    const JQenRender = await LoadJQenRender();
    document.getElementById("container").innerHTML = JQenRender(template, data, "Math Example");
});
```

---

### Inline If

Add conditional logic directly within templates:

```js
const template = `
<div>{if case="{var:one} + {var:two} >= {var:three}" true="3" false="not three"}</div>
<div>{if case="{var:one}" true="{var:one}" false="not one"}</div>
{if case="{var:name} == Qentem" true="<div>Qentem!</div>"}
`;

const data = '{"one":"1","two":"2","three":"3","name":"Qentem"}';

document.addEventListener("DOMContentLoaded", async () => {
    const JQenRender = await LoadJQenRender();
    document.getElementById("container").innerHTML = JQenRender(template, data, "Inline If Example");
});
```

---

### Loop

Render arrays and objects using loops:

```js
const template = `
<loop set="object" value="item">
    <div>{var:item[var1]} {var:item[var2]} {var:item[var3]} {var:item[var4]}</div>
</loop>
<br />
<loop set="array" value="item">
    <div>{var:item[0]} {var:item[1]} {var:item[2]} {var:item[3]}</div>
</loop>
`;

const data = `
{
    "object": [
        {
            "var1": "value1",
            "var2": "value2",
            "var3": "value3",
            "var4": "value4"
        },
        {
            "var1": "value5",
            "var2": "value6",
            "var3": "value7",
            "var4": "value8"
        }
    ],
    "array": [
        [
            "value10",
            "value20",
            "value30",
            "value40"
        ],
        [
            "value100",
            "value200",
            "value300",
            "value400"
        ]
    ]
}`;

document.addEventListener("DOMContentLoaded", async () => {
    const JQenRender = await LoadJQenRender();
    document.getElementById("container").innerHTML = JQenRender(template, data, "Loop Example");
});
```

---

### If Condition

Use full conditional blocks for complex logic:

```js
const template = `
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
<elseif case="{var:2} == 2" />
<div>Two!</div>
<else />
Not zero or one.
</if>

<if case="{var:2} == 0">
Zero!
<elseif case="{var:2} == 5" />
Two!
<elseif case="{var:3} == 3" />
<div>{var:3}</div>
<else />
Not zero or one or two.
</if>`;

const data = "[0,1,2,3]";

document.addEventListener("DOMContentLoaded", async () => {
    const JQenRender = await LoadJQenRender();
    document.getElementById("container").innerHTML = JQenRender(template, data, "If Example");
});
```

---

## Page Example

A complete HTML page using JQen:

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
        <link rel="stylesheet" type="text/css" href="style.css" />
        <title>JQen Page Example</title>
    </head>

    <body>
        <div id="container">
            <fieldset>
                <legend>Template:</legend>
                <textarea id="template_txt" cols="80" rows="18"></textarea>
            </fieldset>
            <fieldset>
                <legend>JSON:</legend>
                <textarea id="json_txt" cols="80" rows="18"></textarea>
            </fieldset>
            <br />
            <fieldset>
                <legend>Result:</legend>
                <textarea id="rendered_txt" cols="80" rows="18"></textarea>
            </fieldset>
            <br />
            <br />
            <button id="render">Render Template</button>
        </div>
        <script src="JQen.js" defer></script>
        <script type="text/javascript">
            "use strict";
            (function () {
                const rt = document.getElementById("rendered_txt"),
                    tt = document.getElementById("template_txt"),
                    jt = document.getElementById("json_txt");

                tt.value = `<h2>Students' list:</h2>
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
                <elseif case='{var:student_val[GPA]} >= 3.0'> (Dean's List!)
                </if>
            </span>
        </li>
    </loop>
    </ul>
</loop>`;

                jt.value = `[
    {
        "major": "Computer Science",
        "students": [
            { "Name": "Student1", "GPA": 3.2 },
            { "Name": "Student2", "GPA": 3.8 },
            { "Name": "Student3", "GPA": 2.8 }
        ]
    },
    {
        "major": "Math",
        "students": [
            { "Name": "Student4", "GPA": 3.0 },
            { "Name": "Student5", "GPA": 2.5 },
            { "Name": "Student6", "GPA": 2.4 }
        ]
    }
]`;

                document.addEventListener("DOMContentLoaded", async () => {
                    const JQenRender = await LoadJQenRender();

                    document.getElementById("render").addEventListener("click", () => {
                        rt.value = JQenRender(tt.value, jt.value);
                    });
                });
            })();
        </script>
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
em++ -std=c++17 -Oz --closure 1 -flto=auto -fno-exceptions \
  -s MODULARIZE=1 \
  -s EXPORT_NAME="JQenModule" \
  -s EXPORTED_FUNCTIONS="['_JQenRender']" \
  -s EXPORTED_RUNTIME_METHODS="['cwrap']" \
  -s ALLOW_MEMORY_GROWTH=1 \
  --extern-post-js ./Source/JQenPost.js \
  -I ./qentem/Include \
  -o Build/JQen.js \
  ./Source/QLib.cpp
```

-   Compiled WASM files and releases:
    [JQen Releases](https://github.com/HaniAmmar/JQen/releases)

---

## License

See the [LICENSE](LICENSE) file for details.
