# JQen

-   [What Is JQen](#what-is-jqen)
-   [Features](#features)
-   [Usage](#usage)
    -   [Variable](#variable)
    -   [Math](#math)
    -   [Inline If](#inline-if)
    -   [Loop](#loop)
    -   [If Condition](#if-condition)
-   [Live Testing](#live-testing)
-   [Page Example](#page-example)
-   [Reference](#reference)
-   [Build WASM](#build-wasm)
-   [License](#license)

## What Is JQen

A JavaScript module that uses [Qentem](https://github.com/HaniAmmar/Qentem-Engine) library for fast template rendering.

## Features

-   Fast template rendering.
-   Low memory usage.
-   Safe evaluation.
-   Variable replacement with HTML auto-escape.
-   Raw variable replacement **without** HTML auto-escape.
-   Nested loop (with data grouping and sorting).
-   Nested if condition.
-   Inline if.
-   Math tag.

## Usage

### Live Test

Templates can be tested live @ [JQen Tool](https://haniammar.github.io/JQen-Tool)

### Variable

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
            "template name" // Optional for caching parsed template.
        );
    },
};
```

### Math

```js
var Module,
    data,
    template = `
<div>0.1+0.2 is: {math: 0.1  +   0.2 }</div>
<div>{var:one}+{var:four}*{var:two}+{var:one} = {math:{var:one}+{var:four}*{var:two}+{var:one}}; (1+8+1)</div>
<div>6^2 = {math:6^2}</div>
<div>{var:one}+{var:three} = {math:{var:one}+{var:three}}</div>
<div>9 % 5 = {math:9 % 5}</div>
`;

data = '{"one":1,"two":2,"three":3,"four":4}';

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(
            template,
            data,
            "template name" // Optional for caching parsed template.
        );
    },
};
```

### Inline If

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
        document.getElementById("main").innerHTML = Module.JQen_Render(
            template,
            data,
            "template name" // Optional for caching parsed template.
        );
    },
};
```

### Loop

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

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(
            template,
            data,
            "template name" // Optional for caching parsed template.
        );
    },
};
```

### If Condition

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

data = "[0,1,2,3]";

Module = {
    onRuntimeInitialized: function () {
        document.getElementById("main").innerHTML = Module.JQen_Render(
            template,
            data,
            "template name" // Optional for caching parsed template.
        );
    },
};
```

## Live Testing

Templates can be tested live @ [JQen Tool](https://haniammar.github.io/JQen-Tool)

## Page Example

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8" />
        <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
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
                        <elseif case="{var:student_val[GPA]} >= 3.5" /> (President's List!)
                        <elseif case="{var:student_val[GPA]} >= 3.0" /> (Dean's List!)
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
                        { Name: "Oliver", GPA: 3.2 },
                        { Name: "Jonah", GPA: 3.8 },
                        { Name: "Jack", GPA: 2.8 },
                    ],
                },
                {
                    major: "Math",
                    students: [
                        { Name: "Maxim", GPA: 3.0 },
                        { Name: "Cole", GPA: 2.5 },
                        { Name: "Claire", GPA: 2.4 },
                    ],
                },
            ];

            Module = {
                onRuntimeInitialized: function () {
                    document.getElementById("main").innerHTML =
                        Module.JQen_Render(
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

## Reference

Syntax @ [Qentem-Engine/Template.md](https://github.com/HaniAmmar/Qentem-Engine/blob/main/Documentation/Template.md).

## Build WASM

Install [Emscripten](https://emscripten.org/docs/getting_started/downloads.html)

Then:

```shell
git submodule update --init

mkdir Build
em++ -lembind -Os -fno-exceptions -std=c++17 -msimd128 -D QENTEM_MSIMD128=1 -I ./qentem/Include ./Source/QLib.cpp -o ./Build/JQen.js
```

**Note**: Compiled WASM file: https://github.com/HaniAmmar/JQen/releases

## License

> MIT License
>
> Copyright (c) 2023 Hani Ammar
>
> Permission is hereby granted, free of charge, to any person obtaining a copy
> of this software and associated documentation files (the "Software"), to deal
> in the Software without restriction, including without limitation the rights
> to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
> copies of the Software, and to permit persons to whom the Software is
> furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all
> copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
> IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
> FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
> AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
> LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
> OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
> SOFTWARE.
