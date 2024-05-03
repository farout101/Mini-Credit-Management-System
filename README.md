<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Mini Credit Transaction System</title>
    <style>
        /* Reset some default styles */
        body, h1, h2, p, ul, li {
            margin: 0;
            padding: 0;
        }
        /* Style the header */
        header {
            background-color: #24292e;
            color: #fff;
            padding: 20px;
            text-align: center;
        }
        header h1 {
            margin-bottom: 10px;
        }
        /* Style the container */
        .container {
            max-width: 800px;
            margin: 0 auto;
            padding: 20px;
        }
        /* Style the table of contents */
        .toc {
            margin-bottom: 20px;
        }
        .toc h2 {
            margin-bottom: 10px;
            color: #0366d6;
        }
        .toc ul {
            list-style-type: none;
            padding-left: 0;
        }
        .toc ul li {
            margin-bottom: 10px;
        }
        .toc ul li a {
            text-decoration: none;
            color: #0366d6;
        }
        .toc ul li a:hover {
            text-decoration: underline;
        }
        /* Style sections */
        section {
            margin-bottom: 30px;
            border-bottom: 1px solid #eaecef;
            padding-bottom: 20px;
        }
        section:last-child {
            border-bottom: none;
        }
        section h2 {
            margin-bottom: 10px;
            color: #0366d6;
        }
        section ul {
            list-style-type: disc;
            margin-left: 20px;
        }
        section ul li {
            margin-bottom: 5px;
        }
        /* Style license section */
        section#license {
            background-color: #f6f8fa;
            padding: 15px;
            border-radius: 5px;
            border: 1px solid #e1e4e8;
            margin-top: 20px;
        }
        section#license p {
            margin-bottom: 10px;
            color: #586069;
        }
    </style>
</head>
<body>
    <header>
        <h1>Mini Credit Transaction System</h1>
        <p>Made with C</p>
    </header>
    <div class="container">
        <div class="toc">
            <h2>Table of Contents</h2>
            <ul>
                <li><a href="#about">About</a></li>
                <li><a href="#features">Features</a></li>
                <li><a href="#installation">Installation</a></li>
                <li><a href="#usage">Usage</a></li>
                <li><a href="#license">License</a></li>
            </ul>
        </div>
        <section id="about">
            <h2>About</h2>
            <p>Just a simplified version of the Mini Banking system.</p>
        </section>
        <section id="features">
            <h2>Features</h2>
            <ul>
                <li>Credit Transfer</li>
                <li>User Control system</li>
                <li>Data storage</li>
            </ul>
        </section>
        <section id="installation">
            <h2>Installation</h2>
            <p>Might need a C compiler to install.</p>
        </section>
        <section id="usage">
            <h2>Usage</h2>
            <ul>
                <li>The first 3 of the registered users are the admins of the system.</li>
                <li>The admins have the privileges of banning, deleting, and monitoring users.</li>
                <li>All Users and Admins can simply transfer their credits to one another.</li>
            </ul>
        </section>
        <section id="license">
            <h2>License</h2>
            <p>
                MIT License
            </p>
            <p>
                Copyright (c) 2024 Far Out
            </p>
            <p>
                Permission is hereby granted, free of charge, to any person obtaining a copy
                of this software and associated documentation files (the "Software"), to deal
                in the Software without restriction, including without limitation the rights
                to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
                copies of the Software, and to permit persons to whom the Software is
                furnished to do so, subject to the following conditions:
            </p>
            <p>
                The above copyright notice and this permission notice shall be included in all
                copies or substantial portions of the Software.
            </p>
            <p>
                THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
                IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
                FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
                AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
                LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
                OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
                SOFTWARE.
            </p>
        </section>
    </div>
</body>
</html>
