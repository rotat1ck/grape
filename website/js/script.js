document.addEventListener('DOMContentLoaded', function() {
    const hero = document.querySelector('.hero-section');
    const heroContent = document.querySelector('.hero-content');
    const heroImage = document.querySelector('.hero-section img'); // Добавляем выбор картинки
    
    if (!hero) return;
    
    let lastScroll = 0;
    let ticking = false;
    
    window.addEventListener('scroll', function() {
        lastScroll = window.scrollY;
        
        if (!ticking) {
            window.requestAnimationFrame(function() {
                updateScrollEffects(lastScroll);
                ticking = false;
            });
            ticking = true;
        }
    });
    
    function updateScrollEffects(scrollPos) {
        const windowHeight = window.innerHeight;
        const scrollPercent = Math.min(scrollPos / windowHeight, 1);
        
        // Только текст двигается вверх с параллаксом
        heroContent.style.transform = `translateY(${scrollPos * 0.5}px)`;
        
        // Плавное исчезновение текста (опционально)
        heroContent.style.opacity = 1 - scrollPercent * 1.2;
        
        // Убираем все трансформации для hero и картинки
        hero.style.transform = 'none';
        if (heroImage) {
            heroImage.style.transform = 'none';
        }
    }
});