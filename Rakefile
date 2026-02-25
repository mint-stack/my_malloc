require "rake/clean"
require "rake/extensiontask"
require "rake/testtask"
require "rdoc/task"

Rake::ExtensionTask.new "my_malloc" do |t|
  t.lib_dir = "lib/my_malloc"
end

Rake::TestTask.new do |t|
end

Rake::RDocTask.new do |t|
  t.main = "README.md"
  t.rdoc_files.include("README.md", "lib/**/*.rb", "ext/**/*.c")
  t.title = "MyMalloc Documentation"
  t.rdoc_dir = "doc"
end

#task :test => [:compile]
task default: :test
