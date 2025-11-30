document.addEventListener('DOMContentLoaded', function() {
  const toggle = document.getElementById('toggle-theme');
  
  if (!toggle) {
    console.error('No se encontro el boton');
    return;
  }
  
  const body = document.body;
  const icon = toggle.querySelector('.fa');
  
  if (!icon) {
    console.error('No se encontro el icono');
    return;
  }
  
  const savedTheme = localStorage.getItem('theme');
  
  if (savedTheme === 'dark') {
    body.classList.add('dark-mode');
    icon.classList.remove('fa-moon');
    icon.classList.add('fa-sun');
  }
  
  toggle.addEventListener('click', function(e) {
    e.preventDefault(); 
    
    body.classList.toggle('dark-mode');
    const isDark = body.classList.contains('dark-mode');
    localStorage.setItem('theme', isDark ? 'dark' : 'light');
    
    if (isDark) {
      icon.classList.remove('fa-moon');
      icon.classList.add('fa-sun');
    } else {
      icon.classList.remove('fa-sun');
      icon.classList.add('fa-moon');
    }
  });
});