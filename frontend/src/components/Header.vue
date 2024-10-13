<script setup lang="ts">
    import { onMounted } from 'vue';
   
    onMounted(() => {
        const hamburger : HTMLElement = document.getElementById('nav-toggle')!;
        const navLinks: HTMLElement = document.getElementById('nav-content')!;
        
        hamburger.addEventListener('click', () => {
            navLinks.classList.toggle("hidden");
        });
    })

</script>

<template>
<nav class="flex items-center justify-between flex-wrap bg-zinc-700 p-6 fixed w-full z-10 top-0">
		<div class="flex items-center text-2xl font-tiny flex-shrink-0 text-white mr-6">
			MyGameStation✨
		</div>

		<div class="block lg:hidden">
			<button id="nav-toggle" class="flex items-center px-3 py-2 border rounded text-gray-500 border-gray-600 hover:text-white hover:border-white">
				<svg class="fill-current h-3 w-3" viewBox="0 0 20 20" xmlns="http://www.w3.org/2000/svg"><title>Menu</title><path d="M0 3h20v2H0V3zm0 6h20v2H0V9zm0 6h20v2H0v-2z"/></svg>
			</button>
		</div>

		<div class="w-full flex-grow lg:flex lg:items-center lg:w-auto hidden lg:block pt-6 lg:pt-0" id="nav-content">
			<ul class="list-reset lg:flex justify-end flex-1 items-center">
				<li class="mr-3">
					<a class="inline-block py-2 px-4 text-white no-underline" href="#">Active</a>
				</li>
				<li class="mr-3">
					<a class="inline-block text-gray-600 no-underline hover:text-gray-200 hover:text-underline py-2 px-4" href="#">link</a>
				</li>
				<li class="mr-3">
					<a class="inline-block text-gray-600 no-underline hover:text-gray-200 hover:text-underline py-2 px-4" href="#">link</a>
				</li>
				<li class="mr-3">
					<a class="inline-block text-gray-600 no-underline hover:text-gray-200 hover:text-underline py-2 px-4" href="#">link</a>
				</li>
			</ul>
		</div>
	</nav>
</template>

<style>

</style>