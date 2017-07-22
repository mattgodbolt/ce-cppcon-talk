(function () {
    var ce_nodes = document.querySelectorAll('.ce');

    for (var i = 0, len = ce_nodes.length; i < len; i++) {
        var element = ce_nodes[i];
        var compiler = "g71";
        var options = "-O1"
        var source = unescape(element.textContent);
        var lines = source.split('\n');
        source = "";
        var matcher = /^\/\/\/\s*([^:]+):(.*)$/;
        for (var idx = 0; idx < lines.length; ++idx) {
            var line = lines[idx];
            var match = line.match(matcher);
            if (match) {
                compiler = match[1];
                options = match[2];
            } else
                source = source + line + "\n";
        }
        var parent = element.parentElement;
        element.remove();
        var ceElement = document.createElement('iframe');
        ceElement.setAttribute('width', '1200px');
        ceElement.setAttribute('height', '300px');
        var content = [];
        content.push({
            type: 'component',
            componentName: 'codeEditor',
            componentState: {
                id: 1,
                source: source,
                options: {compileOnChange: true, colouriseAsm: true},
                fontScale: 1.6
            }
        });
        content.push({
            type: 'component',
            componentName: 'compiler',
            componentState: {
                source: 1,
                filters: {commentOnly: true, directives: true, intel: true, labels: true, trim: true},
                options: options,
                compiler: compiler,
                fontScale: 1.8
            }
        });
        var obj = {
            version: 4,
            content: [{type: 'row', content: content}]
        };
        ceElement.setAttribute('src', "http://localhost:10240/e#" + JSON.stringify(obj));
        parent.appendChild(ceElement);
    }

})();