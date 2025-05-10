console.log("Эщкере");

document.addEventListener('DOMContentLoaded', function() {
    const hero = document.querySelector('.hero-section');
    const heroContent = document.querySelector('.hero-content');
    const heroMask = document.querySelector('.hero-section::after');
    
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
        
        // Плавное исчезновение героя
        hero.style.opacity = 1 - scrollPercent * 1.2;
        
        // Параллакс-эффект для контента
        heroContent.style.transform = `translateY(${scrollPos * 0.3}px)`;
        
        // Появление градиентной маски
        if (heroMask) {
            heroMask.style.opacity = scrollPercent * 1.5;
        }
        
        // Легкое уменьшение масштаба
        const scale = 1 - scrollPercent * 0.1;
        hero.style.transform = `scale(${scale})`;
    }
});