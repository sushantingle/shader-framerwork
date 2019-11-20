<h2>Title</h2>
<p>ShaderFramework</p>
<h2>Installation</h2>
<p>Fork the repository and build it using VS2015.</p>
<h2>Usage</h2>
<p>This framework can be used to implement and test shaders. You can easily add class and shader files in project and check. Currently it supports Vertex, Geometry and Pixel shaders.
To switch between shaders, use 'E' and 'D' keyboard keys.</p>
<h2>Design</h2>
<p>Design approach used here is bit different. I tried to create design pattern using inheritance where base class can have common implementation and derived functions will be called from same.</p>
<pre><code class="language-bash">e.g. base-&gt;BaseInit() ==&gt; 
                        <span class="hljs-function"><span class="hljs-title">BaseInit</span></span>() 
                        { 
                            //default implementation
                            DerivedInit();
                        }
</code></pre>
<h2>Shader Class Structure</h2>
<pre><code class="language-bash">class ShaderDefault : public sf::ShaderInterface {
private :
    void init() override;
    void uninit() override;
    
    void update() override; 
    void render() override;
    
    void renderSnowMan();


public:
    <span class="hljs-function"><span class="hljs-title">ShaderDefault</span></span>() {}
    ~<span class="hljs-function"><span class="hljs-title">ShaderDefault</span></span>() {}
};
</code></pre>
<p>In init, you can add shader files.</p>
<pre><code class="language-bash">addShader(<span class="hljs-number">0</span>, <span class="hljs-string">"toon.vert"</span>, <span class="hljs-string">"toon.frag"</span>, <span class="hljs-string">""</span>);
</code></pre>
<h2></h2>
<p><img src="./ShaderFramework/ReadMe/Screenshot_1.PNG?raw=true" alt="Alt text"></p>
