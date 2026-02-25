Gem::Specification.new "my_malloc", "1.0" do |s|
  s.summary = 'summary'
  s.author = %w[author]
  s.license = 'MIT'
  s.homepage = 'https://github.com/mint-stack/my_malloc'
  s.required_ruby_version = '>= 3.0'

  s.files = Dir['lib/**/*.rb', 'ext/**/*.{c,h}']
  s.extensions = %w[ext/my_malloc/extconf.rb]

  s.add_development_dependency "rake-compiler"
end
